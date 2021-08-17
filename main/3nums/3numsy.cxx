// 3numsy.cxx - read 3 numbers, using exceptions for errors (set by a lambda)

#include <cstdlib>
#include <initializer_list>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    try {
        std::istringstream ss;
        for (std::basic_ios& stream : {std::cout, std::cin, ss})
            stream.exceptions(std::ios_base::failbit | std::ios_base::badbit);

        std::cout << "Enter 3 numbers on a line.\n> ";

        std::string line;
        std::getline(std::cin, line);
        ss.str(line);

        double x, y, z;
        ss >> x >> y >> z;

        std::cout << '(' << x << ", " << y << ", " << z << ")\n";
    }
    catch (std::ios_base::failure&) { return EXIT_FAILURE; }
}