#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <sstream>
#include <string>

namespace {
    bool match(const std::string& text, const std::string& pattern)
    {
        if (pattern.empty()) return true;
        
        const auto n = pattern.size() - 1;
        
        if (pattern[0] == '^') {
            if (pattern[n] == '$')
                return text == pattern.substr(1, n - 1);
            
            return text.substr(0, n) == pattern.substr(1);
        }
        
        if (pattern[n] == '$')
            return text.substr(text.size() - n) == pattern.substr(0, n);
        
        return text.find(pattern) != std::string::npos;
    }
    
    void trim(std::string& str)
    {
        str.erase(str.find_last_not_of(" \t\n\r") + 1u);
    }
    
    std::string getln()
    {
        std::string line;
        std::getline(std::cin, line);
        trim(line);
        return line;
    }
    
    template<typename T>
    T getval()
    {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream in {line};
        
        T x {};
        in >> x;
        return x;
    }
}

int main()
{
    for (auto t = getval<int>(); t > 0; --t) {
        std::string pattern = getln(), text = getln();
        std::cout << match(text, pattern) << '\n';
    }
}
