// line1w.cxx - read+print the 1st line of each file given (wide char version)

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

namespace {
    const char* progname; // set in main
    int status = EXIT_SUCCESS;

    std::ostream& err()
    {
        status = EXIT_FAILURE;
        return std::cerr << progname << ": error: ";
    }

    void line1(const char* path)
    {
        if (std::wifstream in {path}) {
            std::wstring line;
            if (std::getline(in, line)) std::wcout << line << L'\n';
            else err() << "failure while reading \"" << path << "\"\n";
        }
        else err() << "couldn't open file \"" << path << "\"\n";
    }
}

int main(int argc, char* argv[])
{
    progname = argv[0];
    std::for_each(argv + 1, argv + argc, line1);
    return status;
}