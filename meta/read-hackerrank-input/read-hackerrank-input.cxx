// function to read input in one of the styles commonly used on HackerRank

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {
    template<typename T>
    std::vector<T> get_values()
    {
        // get first line
        std::string line;
        std::getline(std::cin, line);
        std::stringstream in {line};
        in.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        
        // read n from first line
        int n {};
        in >> n;
        if (n < 0) n = 0;

        // get second line
        line.erase();
        std::getline(std::cin, line);
        in.str(line);
        in.clear();

        // read values into vector from second line
        std::vector<T> v;
        for (v.reserve(static_cast<decltype(v)::size_type>(n)); n != 0; --n) {
            T x {};
            in >> x
            v.push_back(std::move(x));
        }

        return v;
    }
}

int main()
{

}
