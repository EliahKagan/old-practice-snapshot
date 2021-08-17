#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <set>

namespace {
    class MedianBag {
    public:
        bool empty() const noexcept;

        void add(int value) noexcept;

        bool remove(int value) noexcept; // returns true if removed

        float median() const noexcept;

    private:
        void rebalance() noexcept;

        std::ptrdiff_t delta() const noexcept;

        std::multiset<int, std::greater<>> low_;

        std::multiset<int, std::less<>> high_;
    };

    inline bool MedianBag::empty() const noexcept
    {
        return low_.empty() && high_.empty();
    }

    void MedianBag::add(const int value) noexcept
    {
        if (low_.empty() || *cbegin(low_) < value)
            high_.insert(value);
        else
            low_.insert(value);

        rebalance();
    }

    bool MedianBag::remove(const int value) noexcept
    {
        const auto low_pos = low_.find(value);
        if (low_pos != end(low_)) {
            low_.erase(low_pos);
            rebalance();
            return true;
        }

        const auto high_pos = high_.find(value); // TODO: refactor
        if (high_pos != end(high_)) {
            high_.erase(high_pos);
            rebalance();
            return true;
        }

        return false;
    }

    float MedianBag::median() const noexcept
    {
        switch (delta()) {
        case 0: // even number of values
            if (empty()) std::abort();

            return (static_cast<float>(*cbegin(low_))
                    + static_cast<float>(*cbegin(high_))) / 2.0f;

        case -1: // odd number of values, with the middle in the low values
            return static_cast<float>(*cbegin(low_));

        case +1: // odd number of values, with the middle in the low values
            return static_cast<float>(*cbegin(high_));

        default: // would mean the balancing invariant were violated
            std::abort();
        }
    }

    void MedianBag::rebalance() noexcept
    {
        switch (delta()) {
        case -2: // correctably unbalanced in favor of the low values
            high_.insert(*cbegin(low_));
            low_.erase(cbegin(low_));
            break;

        case +2: // correctably unbalanced in favor of the high values
            low_.insert(*cbegin(high_));
            high_.erase(cbegin(high_));
            break;

        default: // no correctable imbalance
            ;
        }
    }

    inline std::ptrdiff_t MedianBag::delta() const noexcept
    {
        return static_cast<std::ptrdiff_t>(high_.size())
                - static_cast<std::ptrdiff_t>(low_.size());
    }

    void print_value(const float value)
    {
        std::cout << std::setprecision(value == std::nearbyint(value) ? 0 : 1)
                  << value << '\n';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cout << std::fixed;
    MedianBag bag;

    int query_count {};
    for (std::cin >> query_count; query_count > 0; --query_count) {
        char action {};
        int operand {};
        std::cin >> action >> operand;

        switch (action) {
        case 'a':
            bag.add(operand);
            break;

        case 'r':
            if (!bag.remove(operand) || bag.empty()) {
                std::cout << "Wrong!\n";
                continue;
            }

            break;

        default:
            std::abort(); // unrecognized operand
        }

        print_value(bag.median());
    }
}
