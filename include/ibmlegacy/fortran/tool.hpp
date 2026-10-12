#pragma once
#include "ibmlegacy/fortran/diagnostic.hpp"
#include <filesystem>
#include <string>
#include <vector>
namespace ibmlegacy::fortran
{
    // A single analysis finding produced by the FORTRAN language tool.
    struct ToolFinding
    {
        Severity severity{Severity::Note};
        SourceLocation location;
        std::string code;
        std::string message;
    };
    // Structured summary of a source analysis request.
    struct ToolReport
    {
        bool success{false};
        std::string file;
        std::size_t statement_count{0};
        std::size_t line_count{0};
        std::vector<ToolFinding> findings;
        // Machine-readable JSON rendering of the report (for editors/CI).
        [[nodiscard]] std::string to_json() const;
        // Human-readable rendering with file:line:column prefixes.
        [[nodiscard]] std::string to_text() const;
    };
    // Analyses a fixed-form source file: syntax floor check, statement
    // classification, unknown-statement warnings and structural checks.
    [[nodiscard]] ToolReport analyze_fortran_source(const std::filesystem::path &path);
    // Tokenizes every statement and returns lexer diagnostics as findings.
    [[nodiscard]] std::vector<ToolFinding> lint_fortran_source(const std::filesystem::path &path);
} // namespace ibmlegacy::fortran
