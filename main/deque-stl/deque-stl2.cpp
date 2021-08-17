#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <cstdio>
#include <queue>
#include <set>

namespace {
    // Reads an int from cin and adds it to both a bag and a queue.
    inline void read_one(std::multiset<int>& bag, std::queue<int>& window)
    {
        auto elem = 0;
        (void)std::scanf("%d", &elem);
        bag.insert(elem);
        window.push(elem);
    }
}

int main()
{
    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t) {
        auto n = 0, k = 0;
        (void)std::scanf("%d %d", &n, &k);
        assert(0 < k && k <= n);

        std::multiset<int> bag;
        std::queue<int> window; // uses Container=std::deque<int>

        for (int i = k; i != 0; --i) read_one(bag, window);
        std::printf("%d", *bag.crbegin());

        for (n -= k; n != 0; --n) {
            bag.erase(bag.find(window.front())); // discard 1 of oldest element
            window.pop();
            read_one(bag, window);

            std::printf(" %d", *bag.crbegin());
        }

        std::putchar('\n');
    }
}
