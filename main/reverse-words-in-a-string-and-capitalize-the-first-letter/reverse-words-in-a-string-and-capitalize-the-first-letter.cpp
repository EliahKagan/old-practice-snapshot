#include <iostream>
#include <locale>
#include <regex>
#include <sstream>
#include <string>

namespace {
    std::string read_line()
    {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }
    
    template<typename T>
    T read_line_as()
    {
        T x {};
        std::istringstream{read_line()} >> x;
        return x;
    }
}

int main()
{
    const std::locale loc {""};
    const std::regex re {R"([ \t]+|[^ \t]+)", std::regex_constants::optimize};
    const std::sregex_iterator q;
    
    for (auto t = read_line_as<int>(); t > 0; --t) {
        const auto s = read_line();
        
        for (std::sregex_iterator p {s.cbegin(), s.cend(), re}; p != q; ++p) {
            auto w = p->str();
            
            if (w[0] != ' ' && w[0] != '\t') { // could test any char in word
                std::reverse(w.begin(), w.end());
                w[0] = std::toupper(w[0], loc);
            }
            
            std::cout << w;
        }
        
        std::cout << '\n';
    }
}
