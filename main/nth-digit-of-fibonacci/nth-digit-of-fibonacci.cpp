#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

namespace {
    std::vector<int> fibonacci_sequence(const std::vector<int>::size_type size)
    {
        assert(size >= 2u);
        
        std::vector<int> seq;
        seq.reserve(size);

        seq.push_back(1);
        seq.push_back(1);

        for (std::vector<int>::size_type i {2u}; i != size; ++i)
            seq.push_back(seq[i - 2u] + seq[i - 1u]);

        return seq;
    }
}

int main()
{
    constexpr std::vector<int>::size_type sequence_length {30};
    const auto sequence = fibonacci_sequence(sequence_length);

    std::ostringstream ss;
    for (const auto val : sequence) ss << val;
    const auto s = ss.str();
    assert(s.size() >= 100u); // sufficient, according to problem constraints

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type n {};
        std::cin >> n;
        std::cout << s.at(n - 1u) << '\n';
    }
}
