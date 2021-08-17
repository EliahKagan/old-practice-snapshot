#include <array>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

namespace {
    mt19937 get_generator()
    {
        random_device rd;
        return mt19937{rd()};
    }

    int rand7()
    {
        static auto gen = get_generator();
        static uniform_int_distribution<> dist {1, 7};

        return dist(gen);
    }
}

namespace {
    struct OneToSeven {
        using result_type = unsigned;

        static constexpr unsigned min() noexcept { return 1u; }
        static constexpr unsigned max() noexcept { return 7u; }

        result_type operator()() { return static_cast<result_type>(rand7()); }
    };
}

class Solution {
public:
    static int rand10();
};

int Solution::rand10()
{
    static OneToSeven gen;
    static uniform_int_distribution<> dist {1, 10};
    
    return dist(gen);
}


namespace {
    constexpr auto reps = 100'000'000;
    constexpr auto width = 6;

    template<typename F>
    void test(F f)
    {
        // count how often each value is generated
        array<int, 12> freqs {};
        for (auto n = reps; n != 0; --n) ++freqs.at(static_cast<size_t>(f()));

        // output the counts
        for (size_t i {0u}; i != freqs.size(); ++i)
            cout << setw(width) << i << ": " << setw(width) << freqs[i] << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);

    test([]() { return rand7(); });
    cout << endl;
    test([]() { return Solution::rand10(); });
}
