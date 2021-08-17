#include <cassert>
#include <iostream>
#include <iterator>
#include <list>
#include <unordered_map>

namespace {
    class LRU {
    public:
        using size_type = std::list<int>::size_type;
        using const_iterator = std::list<int>::const_iterator;
        using iterator = const_iterator;

        explicit LRU(size_type capacity);

        size_type size() const noexcept { return chain_.size(); }
        size_type capacity() const noexcept { return capacity_; }

        const_iterator cbegin() const noexcept { return std::cbegin(chain_); }
        const_iterator cend() const noexcept { return std::cend(chain_); }
        iterator begin() const noexcept { return cbegin(); }
        iterator end() const noexcept { return cend(); }

        bool bump(int key); // returns true iff a cache miss occurred

    private:
        void move_to_front(const const_iterator node_it) noexcept
        {
            chain_.splice(cbegin(), chain_, node_it);
        }

        std::unordered_map<int, std::list<int>::iterator> table_ {};
        std::list<int> chain_ {};
        const size_type capacity_;
    };

    LRU::LRU(const size_type capacity) : capacity_{capacity}
    {
        if (capacity == 0u)
            throw std::out_of_range{"capacity must be positive"};
    }

    bool LRU::bump(const int key)
    {
        const auto row_it = table_.find(key);

        if (row_it != std::cend(table_)) {
            move_to_front(row_it->second);
            return false;
        }

        if (size() == capacity()) {
            const auto node_it = std::prev(std::end(chain_));
            table_.erase(*node_it);
            *node_it = key;
            move_to_front(node_it);
            table_.emplace(key, node_it);
        } else {
            assert(size() < capacity());
            chain_.push_front(key);
            table_.emplace(key, std::begin(chain_));
        }

        return true;
    }

    std::ostream& operator<<(std::ostream& out, const LRU& cache)
    {
        auto sep = "";
        for (const auto& x : cache) {
            out << sep << x;
            sep = " ";
        }

        return out;
    }
}

int main()
{
    int n {};
    LRU::size_type s {};
    std::cin >> n >> s;

    LRU cache {s};
    auto faults = 0;

    while (n-- > 0) {
        int x {};
        std::cin >> x;
        if (cache.bump(x)) ++faults;
    }

    std::cout << faults << '\n' << cache << '\n';
}
