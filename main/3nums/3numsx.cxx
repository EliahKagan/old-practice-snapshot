// 3numsx.cxx - read 3 numbers, using exceptions for errors

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::cout << "Enter 3 numbers on a line.\n> ";
    
    double x, y, z;
    try {
        constexpr auto failbad {std::ios_base::failbit | std::ios_base::badbit};

        std::cin.exceptions(failbad);
        std::string line;
        std::getline(std::cin, line);

        std::istringstream ss {line};
        ss.exceptions(failbad);
        ss >> x >> y >> z;
    }
    catch (std::ios_base::failure&) { return EXIT_FAILURE; }

    std::cout << '(' << x << ", " << y << ", " << z << ")\n";
}