// line1.cxx - read and print the first line of each file specified

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
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
        if (std::ifstream in {path}) {
            std::string line;
            if (std::getline(in, line)) std::cout << line << '\n';
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