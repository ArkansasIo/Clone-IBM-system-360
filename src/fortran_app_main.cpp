#include "ibmlegacy/fortran/app.hpp"
#include "ibmlegacy/fortran/version.hpp"
#include <iostream>
#include <string>
int main(int argc, char **argv)
{
    using namespace ibmlegacy::fortran;
    if (argc < 2 || std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")
    {
        std::cout << "IBM Legacy FORTRAN application runner " << IBMLEGACY_FORTRAN_VERSION_MAJOR << '.' << IBMLEGACY_FORTRAN_VERSION_MINOR << '.' << IBMLEGACY_FORTRAN_VERSION_PATCH << '\n'
                  << "Usage:\n  ibm-fortran-app <source.f>   Run a fixed-form source file\n  ibm-fortran-app --repl       Start the interactive REPL\n  ibm-fortran-app --version    Print version\n"
                  << "Dialect: " << IBMLEGACY_FORTRAN_DIALECT << '\n';
        return 0;
    }
    std::string mode = argv[1];
    if (mode == "--version")
    {
        std::cout << IBMLEGACY_FORTRAN_VERSION_MAJOR << '.' << IBMLEGACY_FORTRAN_VERSION_MINOR << '.' << IBMLEGACY_FORTRAN_VERSION_PATCH << '\n';
        return 0;
    }
    if (mode == "--repl")
        return run_fortran_repl(std::cin, std::cout);
    const auto run = run_fortran_source(mode);
    std::cerr << run.diagnostics;
    std::cout << run.output;
    return run.success ? 0 : 1;
}
