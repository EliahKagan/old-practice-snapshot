#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    std::vector<int> read_values()
    {
        std::vector<int>::size_type t {};
        std::cin >> t;
        std::vector<int> values;

        for (values.reserve(t); t != 0u; --t) {
            auto n = 0;
            std::cin >> n;
            values.push_back(n);
        }

        return values;
    }

    int max_value(const std::vector<int>& values)
    {
        if (values.size() == 0) return 0;
        return *std::max_element(values.cbegin(), values.cend());
    }

    std::vector<int> fibonacci_upto(const int stop)
    {
        std::vector<int> seq;

        seq.push_back(0);
        seq.push_back(1);

        for (std::vector<int>::size_type i {0u}; ; ) {
            auto val = seq[i];
            val += seq[++i];
            seq.push_back(val);
            if (val >= stop) return seq;
        }
    }
}

int main()
{
    const auto values = read_values();
    const auto seq = fibonacci_upto(max_value(values));

    for (const auto n : values) {
        auto is_fibonacci = std::binary_search(seq.cbegin(), seq.cend(), n);
        std::cout << (is_fibonacci ? "Yes" : "No") << '\n';
    }
}
