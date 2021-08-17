#include<iostream>
#include<limits.h>
using namespace std;
#define N 1000
void findSmallestRange(int arr[][N], int n, int k);
// Driver program to test above functions
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n, k;
        cin>>n>>k;
        int arr[N][N];
        for(int i=0; i<k; i++)
            for(int j=0; j<n; j++)
                cin>>arr[i][j];
	    findSmallestRange(arr, n, k);
    }   
	return 0;
}

/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {
    class AndCounter {
    public:
        explicit AndCounter(size_t size);
        void add(unsigned item) noexcept;
        void remove(unsigned item) noexcept;
        bool goal_met() const noexcept;

    private:
        std::vector<unsigned> targets_;
        std::size_t need_;
    };

    AndCounter::AndCounter(const size_t size) : targets_(size), need_{size}
    {
    }

    inline void AndCounter::add(const unsigned item) noexcept
    {
        if (targets_[item]++ == 0u) --need_;
    }

    inline void AndCounter::remove(const unsigned item) noexcept
    {
        if (--targets_[item] == 0u) ++need_;
    }

    inline bool AndCounter::goal_met() const noexcept
    {
        return need_ == 0u;
    }

    struct Element {
        int value;
        unsigned row_id;
    };

    constexpr bool operator<(const Element& lhs, const Element& rhs) noexcept
    {
        return lhs.value < rhs.value;
    }

#ifdef __GNUC__
    [[gnu::unused]]
#endif
    constexpr bool operator>(const Element& lhs, const Element& rhs) noexcept
    {
        return lhs.value > rhs.value;
    }

    vector<Element> flatten(int arr[][N], const unsigned n, const unsigned k)
    {
        std::vector<Element> a (n * k);
        auto p = begin(a);

        for (auto row_id = 0u; row_id < k; ++row_id) {
            for (auto col_index = 0u; col_index < n; ++col_index) {
                p->value = arr[row_id][col_index];
                p->row_id = row_id;
                ++p;
            }
        }

        assert(p == end(a));
        return a;
    }

    inline void update_min_range(pair<int, int>& range,
                                 const int first, const int second) noexcept
    {
        if (second - first < range.second - range.first) {
            range.first = first;
            range.second = second;
        }
    }

    pair<int, int> find_min_range(const vector<Element>& a,
                                  AndCounter& counter) noexcept
    {
        auto range = make_pair(a.front().value, a.back().value);

        const auto last = a.cend();
        for (auto left = a.cbegin(), right = left; ; ) {
            for (; !counter.goal_met() && right != last; ++right)
                counter.add(right->row_id);

            if (!counter.goal_met()) break;

            for (; counter.goal_met(); ++left)
                counter.remove(left->row_id);

            update_min_range(range, prev(left)->value, prev(right)->value);
        }

        return range;
    }
}

// you are required to complete this function 
// function should print the required range
void findSmallestRange(int arr[][N], int n, int k)
{
    auto a = flatten(arr, static_cast<unsigned>(n), static_cast<unsigned>(k));
    if (a.empty()) throw std::invalid_argument{"there are no values"};
    sort(std::begin(a), std::end(a));

    AndCounter counter {static_cast<size_t>(k)};

    const auto range = find_min_range(a, counter);
    cout << range.first << ' ' << range.second << '\n';
}
