#include <cmath>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>

namespace {
    double eval_left_to_right(std::istream& in)
    {
        double acc {};
        in >> acc;
        
        char op {};
        double arg {};
        while (in >> op >> arg) {
            switch (op) {
                case '+':   acc += arg;     continue;
                case '-':   acc -= arg;     continue;
                case '*':   acc *= arg;     continue;
                case '/':   acc /= arg;     continue;
                default:    throw std::domain_error{"unrecognized operator"};
            }
        }

        return std::floor(acc);
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t >> std::ws; t > 0; --t) {
        std::string s;
        std::cin >> s;
        std::istringstream ss {s};
        std::cout << std::llround(eval_left_to_right(ss)) << '\n';
    }
}
