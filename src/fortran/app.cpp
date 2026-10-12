#include "ibmlegacy/fortran/app.hpp"
#include "ibmlegacy/fortran/expression.hpp"
#include "ibmlegacy/fortran/parser.hpp"
#include "ibmlegacy/fortran/source_reader.hpp"
#include "ibmlegacy/fortran/symbol_table.hpp"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
namespace ibmlegacy::fortran
{
    namespace
    {
        std::string trim(std::string s)
        {
            // Drop a UTF-8/UTF-16 byte-order mark that editors may prepend.
            if (s.size() >= 3 && static_cast<unsigned char>(s[0]) == 0xEF && static_cast<unsigned char>(s[1]) == 0xBB && static_cast<unsigned char>(s[2]) == 0xBF)
                s.erase(0, 3);
            auto p = [](unsigned char c)
            { return !std::isspace(c); };
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), p));
            s.erase(std::find_if(s.rbegin(), s.rend(), p).base(), s.end());
            return s;
        }
        std::string upper(std::string s)
        {
            for (char &c : s)
                c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
            return s;
        }
        bool starts(const std::string &s, const std::string &w) { return s == w || (s.size() > w.size() && s.compare(0, w.size(), w) == 0 && std::isspace(static_cast<unsigned char>(s[w.size()]))); }

        // Splits "A = B + 1" into {"A","B + 1"}; returns false when there is no '='.
        bool split_assignment(const std::string &s, std::string &lhs, std::string &rhs)
        {
            auto eq = s.find('=');
            if (eq == std::string::npos)
                return false;
            if (s.find("==") != std::string::npos)
                return false;
            lhs = trim(s.substr(0, eq));
            rhs = trim(s.substr(eq + 1));
            return !lhs.empty();
        }

        class Interpreter
        {
        public:
            Interpreter(std::ostream &out, std::map<std::string, double> *shared = nullptr)
                : out_(out), external_(shared) {}
            bool execute_statement(const std::string &source, std::string &error);

        private:
            std::map<std::string, double> &values() { return external_ ? *external_ : local_; }
            std::ostream &out_;
            std::map<std::string, double> local_;
            std::map<std::string, double> *external_{nullptr};
            SymbolTable symbols_;
        };
    } // namespace

    bool Interpreter::execute_statement(const std::string &source, std::string &error)
    {
        auto u = upper(trim(source));
        if (u.empty() || u == "END" || starts(u, "PROGRAM") || u == "CONTINUE" || u == "RETURN")
            return true;
        if (u == "STOP" || u.rfind("STOP ", 0) == 0)
            return true;
        if (starts(u, "INTEGER") || starts(u, "REAL") || starts(u, "LOGICAL") || starts(u, "DOUBLE PRECISION") || starts(u, "COMPLEX"))
        {
            auto space = u.find(' ');
            auto list = source.substr(std::min(space + 1, source.size()));
            std::stringstream items(list);
            std::string item;
            while (std::getline(items, item, ','))
            {
                auto name = trim(item);
                if (name.empty())
                    continue;
                auto paren = name.find('(');
                if (paren != std::string::npos)
                    name = trim(name.substr(0, paren));
                TypeKind k = TypeKind::Real;
                if (starts(u, "INTEGER"))
                    k = TypeKind::Integer;
                else if (starts(u, "LOGICAL"))
                    k = TypeKind::Logical;
                (void)symbols_.declare({name, k, true, std::nullopt});
                values().try_emplace(upper(name), 0.0);
            }
            return true;
        }
        if (starts(u, "PRINT"))
        {
            auto pos = source.find(',');
            std::string args = pos == std::string::npos ? std::string{} : trim(source.substr(pos + 1));
            if (args == "*" || args.empty())
            {
                out_ << '\n';
                return true;
            }
            std::stringstream exprs(args);
            std::string e;
            bool first = true;
            while (std::getline(exprs, e, ','))
            {
                e = trim(e);
                if (e.empty())
                    continue;
                if (!first)
                    out_ << ' ';
                first = false;
                if (e.size() >= 2 && (e.front() == '\'' || e.front() == '"') && e.back() == e.front())
                    out_ << e.substr(1, e.size() - 2);
                else
                {
                    auto r = evaluate_numeric_expression(e, values());
                    if (!r.success)
                    {
                        error = "Cannot evaluate PRINT item: " + e;
                        return false;
                    }
                    out_ << r.value;
                }
            }
            out_ << '\n';
            return true;
        }
        std::string lhs, rhs;
        if (split_assignment(source, lhs, rhs))
        {
            auto name = trim(lhs);
            std::size_t p = name.find('(');
            if (p != std::string::npos)
                name = trim(name.substr(0, p));
            auto r = evaluate_numeric_expression(rhs, values());
            if (!r.success)
            {
                error = "Cannot evaluate expression: " + rhs;
                return false;
            }
            values()[upper(name)] = r.value;
            return true;
        }
        error = "Unsupported statement in runner: " + source;
        return false;
    }

    AppRunResult run_fortran_source(const std::filesystem::path &path)
    {
        AppRunResult result;
        auto parsed = parse_fortran_source(path);
        if (!parsed.success)
        {
            result.diagnostics = "Failed to parse source\n";
            return result;
        }
        std::ostringstream out;
        Interpreter interpreter(out);
        for (const auto &stmt : parsed.program.statements)
        {
            std::string error;
            if (!interpreter.execute_statement(stmt.source, error))
            {
                std::ostringstream d;
                d << stmt.location.file << ':' << stmt.location.line << ": runtime error: " << error << '\n';
                if (!result.diagnostics.empty())
                    result.diagnostics += '\n';
                result.diagnostics += d.str();
                result.success = false;
                return result;
            }
        }
        for (const auto &diag : parsed.diagnostics)
        {
            if (diag.severity == Severity::Error)
            {
                std::ostringstream d;
                d << diag.location.file << ':' << diag.location.line << ": error " << diag.code << ": " << diag.message << '\n';
                result.diagnostics += d.str();
                result.success = false;
            }
        }
        result.output = out.str();
        result.success = result.diagnostics.empty();
        return result;
    }

    FortranRepl::FortranRepl(std::istream &in, std::ostream &out) : in_(in), out_(out) {}

    void FortranRepl::banner() const
    {
        out_ << "IBM Legacy FORTRAN subset REPL (experimental)\n";
        out_ << "Type an expression, an assignment, PRINT or QUIT/EXIT.\n";
    }

    bool FortranRepl::handle_line(const std::string &line)
    {
        auto text = trim(line);
        if (text.empty())
            return true;
        auto u = upper(text);
        if (u == "QUIT" || u == "EXIT" || u == "BYE")
            return false;
        if (u == "HELP")
        {
            banner();
            out_ << "Examples:\n  A = 2 ** 3 + 1\n  PRINT *, A\n";
            return true;
        }
        Interpreter probe(out_, &variables_);
        std::string error;
        if (!probe.execute_statement(text, error))
        {
            auto expr = evaluate_numeric_expression(text, variables_);
            if (expr.success)
            {
                out_ << expr.value << '\n';
                return true;
            }
            out_ << "Error: " << error << '\n';
            return true;
        }
        return true;
    }

    int run_fortran_repl(std::istream &in, std::ostream &out)
    {
        FortranRepl repl(in, out);
        repl.banner();
        std::string line;
        while (true)
        {
            out << "f>";
            if (!std::getline(in, line))
                break;
            if (!repl.handle_line(line))
                break;
        }
        out << '\n';
        return 0;
    }
} // namespace ibmlegacy::fortran
