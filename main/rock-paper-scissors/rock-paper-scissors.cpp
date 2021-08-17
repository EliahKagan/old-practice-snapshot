#include <iostream>
#include <stdexcept>

namespace {
    const char* outcome(const char a, const char b)
    {
        switch (a) {
        case 'P':
            switch (b) {
            case 'P':
                return "DRAW";
            case 'R':
                return "A";
            case 'S':
                return "B";
            default:
                throw std::invalid_argument{"b"};
            }

        case 'R':
            switch (b) {
            case 'P':
                return "B";
            case 'R':
                return "DRAW";
            case 'S':
                return "A";
            default:
                throw std::invalid_argument{"b"};
            }

        case 'S':
            switch (b) {
            case 'P':
                return "A";
            case 'R':
                return "B";
            case 'S':
                return "DRAW";
            default:
                throw std::invalid_argument{"b"};
            }

        default:
            throw std::invalid_argument{"a"};
        }
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto a = '\0', b = '\0';
        std::cin >> a >> b;
        std::cout << outcome(a, b) << '\n';
    }
}
