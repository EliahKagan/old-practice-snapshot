#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    // Reads whitespace-separated digits.
    std::vector<int> get_digits()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;
        
        std::vector<int> a;
        a.reserve(n + 1u);
        a.push_back(0); // ensuring a leading zero simplifies the algorithm
        
        while (n-- != 0u) {
            auto d = 0;
            std::cin >> d;
            a.push_back(d);
        }

        return a;
    }

    // Writes line of space-separated digts. Preserves any original extra
    // leading zeros, even though it's rather silly to do so. (The solution
    // checker appears to require this.)
    void put_digits(const std::vector<int>& a, const bool carry)
    {
        auto sep = "";
        auto p = a.cbegin();

        const auto put = [&]() {
            std::cout << sep << *p;
            sep = " ";
        };

        if (carry) put(); // print the leading digit, as we carried into it
        while (++p != a.cend()) put();
        std::cout << '\n';
    }

    // Changes the digits in a so they represent the next integer (that is,
    // adds one to a). Returns true if this causes a carry in the leading
    // digit, and false otherwise.
    bool increment_digits(std::vector<int>& a)
    {
        auto p = std::find_if(a.rbegin(), a.rend(),
                              [](const int d) { return d != 9; });
        ++(*p);
        
        std::for_each(a.rbegin(), p, [](int& d) { d = 0; });
        return ++p == a.rend();
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto a = get_digits();
        put_digits(a, increment_digits(a));
    }
}
