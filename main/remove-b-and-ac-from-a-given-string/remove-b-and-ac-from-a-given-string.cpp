#include <iostream>
#include <sstream>
#include <string>

namespace {
    std::string getln()
    {
        std::string s;
        std::getline(std::cin, s);
        return s;
    }

    int read_t_val()
    {
        auto t = 0;
        std::istringstream{getln()} >> t;
        return t;
    }

    std::string remove_b_and_ac(std::string&& s)
    {
        auto p = s.begin();

        for (auto q = s.cbegin(); q != s.cend(); ++q) {
            if (*q == 'b') continue;

            if (*q == 'a') {
                const auto r = q + 1;
                if (r != s.cend() && *r == 'c') {
                    ++q;
                    continue;
                }
            }

            *(p++) = *q;
        }

        s.erase(p, s.end()); // for GCC 4.8.4 (C++11 s.cend() won't work here)
        return s;
    }
}

int main()
{
    for (auto t = read_t_val(); t > 0; --t)
        std::cout << remove_b_and_ac(getln()) << '\n';
}
