// square.cxx - square a number given as a command line arg or interactively

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace {
    const char* progname; // set in main(int, char*[])

    [[noreturn]] void die(const std::string& msg)
    {
        std::cerr << progname << ": error: " << msg << '\n';
        std::exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[])
{
    progname = argv[0];
    const auto f = [](double x) { return x * x; };
    const auto do_f
        = [&f](double x) { std::cout << "f(" << x << ") = " << f(x) << '\n'; };

    if (argc > 1) {
        try { do_f(std::stod(argv[1])); }
        catch (const std::invalid_argument&) { die("non-numeric input"); }
        catch (const std::out_of_range&) { die("input out of range"); }
    } else {
        std::cout << "Hark! Please bring your ingenuity to bear...\n"
                     "...and enter the number you want me to square!\n";
        for (std::string line; ; std::cin.clear()) {
            std::cout << "> ";
            if (!std::getline(std::cin, line)) die("couldn't read from stdin");
            if (line.empty()) break;

            std::istringstream ss {line};
            ss.exceptions(std::ios_base::badbit);
            double y;
            if (!(ss >> y >> std::ws)) {
                std::cout << "That was a number... "
                             "in the world of your mind.\n";
            }
            else if (ss.eof()) do_f(y);
            else std::cout << "Just one number, please -- nothing else.\n";
        }
    }

    std::cout << "Bye!\n";
}