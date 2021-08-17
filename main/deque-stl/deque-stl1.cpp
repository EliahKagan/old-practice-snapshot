#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <iostream>
#include <queue>
#include <set>

namespace {
    // Reads an int from cin and adds it to both a bag and a queue.
    inline void read_one(std::multiset<int>& bag, std::queue<int>& window)
    {
        auto elem = 0;
        std::cin >> elem;
        bag.insert(elem);
        window.push(elem);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0, k = 0;
        std::cin >> n >> k;
        assert(0 < k && k <= n);

        std::multiset<int> bag;
        std::queue<int> window; // uses Container=std::deque<int>

        for (int i = k; i != 0; --i) read_one(bag, window);
        std::cout << *bag.crbegin();

        for (n -= k; n != 0; --n) {
            bag.erase(bag.find(window.front())); // discard 1 of oldest element
            window.pop();
            read_one(bag, window);

            std::cout << ' ' << *bag.crbegin();
        }

        std::cout << '\n';
    }
}
