#include <iostream>
#include <set>
#include <sstream>
#include <string>

namespace {
    std::set<std::string> get_substrings(const std::string& s)
    {
        std::set<std::string> subs;
        
        for (std::string::size_type i {0u}; i != s.size(); ++i) {
            for (std::string::size_type j {1u}; i + j <= s.size(); ++j)
                subs.insert(s.substr(i,  j));
        }
        
        return subs;
    }
    
    std::string concatenate(const std::set<std::string>& ss)
    {
        std::ostringstream os;
        for (const auto& s : ss) {
            std::cout << s << ' ';
            os << s;
        }
        std::cout << '"' << os.str() << "\"\n";
        return os.str();
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::string::size_type i {};
        std::cin >> s >> i;
        
        std::cout << concatenate(get_substrings(s)).at(i - 1u) << '\n';
    }
}
