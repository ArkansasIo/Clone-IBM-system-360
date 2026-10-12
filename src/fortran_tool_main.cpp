#include "ibmlegacy/fortran/tool.hpp"
#include "ibmlegacy/fortran/version.hpp"
#include <iostream>
#include <string>
int main(int argc, char **argv)
{
    using namespace ibmlegacy::fortran;
    if (argc < 2 || std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")
    {
        std::cout << "IBM Legacy FORTRAN language tool " << IBMLEGACY_FORTRAN_VERSION_MAJOR << '.' << IBMLEGACY_FORTRAN_VERSION_MINOR << '.' << IBMLEGACY_FORTRAN_VERSION_PATCH << '\n'
                  << "Usage:\n  ibm-fortran-tool <source.f> [--json]   Analyze a source file\n  ibm-fortran-tool --version\n";
        return 0;
    }
    std::string first = argv[1];
    if (first == "--version")
    {
        std::cout << IBMLEGACY_FORTRAN_VERSION_MAJOR << '.' << IBMLEGACY_FORTRAN_VERSION_MINOR << '.' << IBMLEGACY_FORTRAN_VERSION_PATCH << '\n';
        return 0;
    }
    bool json = false;
    std::string source = first;
    for (int i = 2; i < argc; ++i)
    {
        std::string a = argv[i];
        if (a == "--json")
            json = true;
    }
    const auto report = analyze_fortran_source(source);
    std::cout << (json ? report.to_json() : report.to_text());
    return report.success ? 0 : 1;
}
