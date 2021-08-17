// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

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
