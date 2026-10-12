#include "ibmlegacy/fortran/tool.hpp"
#include "ibmlegacy/fortran/lexer.hpp"
#include "ibmlegacy/fortran/parser.hpp"
#include "ibmlegacy/fortran/source_reader.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
namespace ibmlegacy::fortran
{
   namespace
   {
      std::string trim(std::string s)
      {
         auto p = [](unsigned char c)
         { return !std::isspace(c); };
         s.erase(s.begin(), std::find_if(s.begin(), s.end(), p));
         s.erase(std::find_if(s.rbegin(), s.rend(), p).base(), s.end());
         return s;
      }
      std::string json_escape(const std::string &s)
      {
         std::string out;
         for (char c : s)
         {
            switch (c)
            {
            case '"':
               out += "\\\"";
               break;
            case '\\':
               out += "\\\\";
               break;
            case '\n':
               out += "\\n";
               break;
            case '\t':
               out += "\\t";
               break;
            default:
               out += c;
            }
         }
         return out;
      }
      const char *severity_name(Severity s)
      {
         switch (s)
         {
         case Severity::Error:
            return "error";
         case Severity::Warning:
            return "warning";
         default:
            return "note";
         }
      }
   } // namespace

   std::string ToolReport::to_json() const
   {
      std::ostringstream out;
      out << "{\"file\":\"" << json_escape(file) << "\",\"success\":" << (success ? "true" : "false")
          << ",\"line_count\":" << line_count << ",\"statement_count\":" << statement_count << ",\"findings\":[";
      for (std::size_t i = 0; i < findings.size(); ++i)
      {
         const auto &f = findings[i];
         if (i)
            out << ',';
         out << "{\"severity\":\"" << severity_name(f.severity) << "\",\"code\":\"" << json_escape(f.code)
             << "\",\"line\":" << f.location.line << ",\"column\":" << f.location.column << ",\"message\":\"" << json_escape(f.message) << "\"}";
      }
      out << "]}";
      return out.str();
   }

   std::string ToolReport::to_text() const
   {
      std::ostringstream out;
      out << file << ": " << statement_count << " statements, " << findings.size() << " findings\n";
      for (const auto &f : findings)
         out << file << ':' << f.location.line << ':' << f.location.column << ": " << severity_name(f.severity) << ' ' << f.code << ": " << f.message << '\n';
      return out.str();
   }

   std::vector<ToolFinding> lint_fortran_source(const std::filesystem::path &path)
   {
      std::vector<ToolFinding> findings;
      auto read = read_fixed_form_source(path);
      if (!read.success)
      {
         findings.push_back({Severity::Error, {path.string(), 1, 1}, "FTOOL001", read.diagnostic});
         return findings;
      }
      for (const auto &rec : read.records)
      {
         auto text = trim(rec.statement);
         if (text.empty())
            continue;
         if (text.size() > 66)
            findings.push_back({Severity::Warning, {path.string(), rec.line_number, 73}, "FTOOL002", "Statement text may exceed the fixed-form field (columns 7-72)"});
         auto lexed = lex_statement(text, path.string(), rec.line_number);
         for (const auto &d : lexed.diagnostics)
            findings.push_back({d.severity, d.location, d.code, d.message});
      }
      return findings;
   }

   ToolReport analyze_fortran_source(const std::filesystem::path &path)
   {
      ToolReport report;
      report.file = path.string();
      auto parsed = parse_fortran_source(path);
      if (!parsed.success)
      {
         report.findings.push_back({Severity::Error, {path.string(), 1, 1}, "FTOOL001", "Failed to parse source"});
         return report;
      }
      report.line_count = parsed.program.statements.empty() ? 0 : parsed.program.statements.back().location.line;
      report.statement_count = parsed.program.statements.size();
      bool has_end = false;
      for (const auto &stmt : parsed.program.statements)
      {
         if (stmt.kind == StatementKind::Unknown)
            report.findings.push_back({Severity::Warning, stmt.location, "FTOOL010", "Statement kind is unknown to the current scaffold"});
         if (stmt.kind == StatementKind::End)
            has_end = true;
      }
      if (report.statement_count > 0 && !has_end)
         report.findings.push_back({Severity::Warning, {path.string(), report.line_count, 1}, "FTOOL011", "No END statement found"});
      for (const auto &d : parsed.diagnostics)
         report.findings.push_back({d.severity, d.location, d.code, d.message});
      for (const auto &f : lint_fortran_source(path))
         report.findings.push_back(f);
      report.success = std::none_of(report.findings.begin(), report.findings.end(), [](const ToolFinding &f)
                                    { return f.severity == Severity::Error; });
      return report;
   }
} // namespace ibmlegacy::fortran
