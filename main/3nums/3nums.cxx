// 3nums.cxx - read 3 numbers

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::cout << "Enter 3 numbers on a line.\n> ";
    std::string line;
    if (!std::getline(std::cin, line)) return EXIT_FAILURE;
    
    std::istringstream ss {line};
    double x, y, z;
    if (!(ss >> x >> y >> z)) return EXIT_FAILURE;

    std::cout << '(' << x << ", " << y << ", " << z << ")\n";
}