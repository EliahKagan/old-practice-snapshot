#include <cassert>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace {
    std::string zero_pad(const std::string& str,
                         const std::string::size_type n)
    {
        assert(str.size() <= n);
        return std::string(n - str.size(), '0') + str;
    }

    std::vector<int> get_digit_vector(const std::string& str)
    {
        std::vector<int> digits;
        digits.reserve(str.size());
        for (const auto ch : str) digits.push_back(ch - '0');
        return digits;
    }

    void print_binary_sum(const std::vector<int>& a,
                          const std::vector<int>& b)
    {
        assert(a.size() == b.size());

        std::stack<int> sum;
        auto carry = 0;
        
        for (auto p = a.crbegin(), q = b.crbegin(); p != a.crend(); ++p, ++q) {
            const auto s = *p + *q + carry, d = s % 2;
            sum.push(d);
            carry = (s == d ? 0 : 1);
        }

        if (carry != 0) sum.push(1);

        while (!sum.empty()) {
            std::cout << sum.top();
            sum.pop();
        }

        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string x, y;
        std::cin >> x >> y;

        const auto big_x = x.size() > y.size();

        const std::string& large {big_x ? x : y};
        const std::string& small {big_x ? y : x};

        print_binary_sum(get_digit_vector(large),
                         get_digit_vector(zero_pad(small, large.size())));
    }
}
