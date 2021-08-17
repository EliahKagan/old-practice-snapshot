#include <cassert>
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>
#include <unordered_map>

using namespace std;

class LRUCache {
public:
    static constexpr auto not_found = -1;

    explicit LRUCache(int capacity);

    int get(int key) noexcept;

    void put(int key, int value);

private:
    struct KeyValuePair {
        int key, value;

        KeyValuePair(const int key, const int value)
            : key{key}, value{value} { }
    };

    void bump(const list<KeyValuePair>::const_iterator pos) // splices to front
    {
        chain_.splice(cbegin(chain_), chain_, pos);
    }

    unordered_map<int, list<KeyValuePair>::iterator> lookup_;
    list<KeyValuePair> chain_;
    const list<KeyValuePair>::size_type capacity_;
};

LRUCache::LRUCache(const int capacity)
    : capacity_{static_cast<list<KeyValuePair>::size_type>(capacity)}
{
    if (capacity <= 0)
        throw invalid_argument{"capacity must be strictly positive"};
}

int LRUCache::get(const int key) noexcept
{
    const auto it = lookup_.find(key);
    if (it == end(lookup_)) return not_found;

    const auto pos = it->second;
    bump(pos);
    return pos->value;
}

void LRUCache::put(const int key, const int value)
{
    const auto it = lookup_.find(key);

    if (it != end(lookup_)) {
        const auto pos = it->second;
        pos->value = value;
        bump(pos);
    }
    else if (chain_.size() == capacity_) {
        const auto pos = prev(end(chain_)); // reuse back (least recent) node
        lookup_.erase(pos->key);

        pos->key = key;
        pos->value = value;
        bump(pos);
        lookup_.emplace(key, pos);
    } else {
        assert(chain_.size() < capacity_);

        chain_.emplace_front(key, value);
        lookup_.emplace(key, begin(chain_));
    }
}

int main()
{
    LRUCache cache{2};

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << '\n';
    cache.put(3, 3);
    cout << cache.get(2) << '\n';
    cache.put(4, 4);
    cout << cache.get(1) << '\n';
    cout << cache.get(3) << '\n';
    cout << cache.get(4) << '\n';
}
