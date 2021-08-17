#include <iostream>
#include <iterator>

namespace {
    template<typename Element, typename Iterator>
    bool has_pair_sum(Iterator start, Iterator stop, Element sum)
    {
        if (start == stop) return false;

        for (--stop; start != stop; ) {
            const auto s = *start + *stop;
            if (s == sum) return true;

            if (s < sum) ++start;
            else --stop;
        }

        return false;
    }
}

int main()
{
    using std::cbegin;
    using std::cend;

    int a[] {1, 2, 3, 9}, b[] {1, 2, 4, 4}, c[] {1, 2};
    
    std::cout << std::boolalpha
        << has_pair_sum(cbegin(a), cend(a), 8) << '\n'
        << has_pair_sum(cbegin(b), cend(b), 8) << '\n'
        << has_pair_sum(cbegin(c), cend(c), 3) << '\n'
        << has_pair_sum(cbegin(c), cend(c), 2) << '\n';
}
