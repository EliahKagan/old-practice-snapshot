#include <iostream>
#include <string>

namespace {
    void print_indices(const std::string& text, const std::string& pattern)
    {
        using std::string;
        using Index = string::size_type;
        
        auto found = false;
        for (Index i {0u}; (i = text.find(pattern, i)) != string::npos; ) {
            if (found) std::cout << ' ';
            std::cout << ++i;
            found = true;
        }

        if (!found) std::cout << -1;
        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string text, pattern;
        std::cin >> text >> pattern;
        print_indices(text, pattern);
    }
}
