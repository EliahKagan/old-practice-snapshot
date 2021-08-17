#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>
#include <unordered_map>

class LFUCache {
public:
    explicit LFUCache(int capacity);

    LFUCache(const LFUCache&) = delete;
    LFUCache(LFUCache&&) = default;
    LFUCache& operator=(const LFUCache&) = delete;
    LFUCache& operator=(LFUCache&&) = default;
    ~LFUCache() = default;

    int get(int key);

    void put(int key, int value);

private:
    struct Group;

    struct Entry {
        // Allows Entry objects to be emplaced.
        Entry(std::list<Group>::iterator group, int key, int value) noexcept;

        std::list<Group>::iterator group;
        int key, value;
    };

    struct Group {
        explicit Group(unsigned frequency) noexcept;

        std::list<Entry> entries;
        unsigned frequency;
    };

    static constexpr auto not_found = -1;

    static void move_to_group(std::list<Entry>::iterator entry,
                              std::list<Group>::iterator group) noexcept;

    void bump(std::list<Entry>::iterator entry);

    void reuse(std::list<Entry>::iterator entry);

    std::list<Entry>::iterator make(int key, int value);

    std::unordered_map<int, std::list<Entry>::iterator> map_;

    std::list<Group> groups_;

    int vacancy_;
};

LFUCache::LFUCache(const int capacity) : vacancy_{capacity}
{
    if (capacity < 0) throw std::out_of_range{"negative capacity not allowed"};
}

int LFUCache::get(const int key)
{
    const auto p = map_.find(key);
    if (p == std::end(map_)) return not_found;

    const auto entry = p->second;
    bump(entry);
    return entry->value;
}

void LFUCache::put(const int key, const int value)
{
    const auto p = map_.find(key);

    if (p != std::end(map_)) {
        const auto entry = p->second;
        entry->value = value;
        bump(entry);
    }
    else if (vacancy_ != 0) {
        assert(vacancy_ > 0);
        --vacancy_; // TODO: change here *and elsewhere* for exception safety
        map_.emplace(key, make(key, value));
    }
    else if (!groups_.empty()) {
        const auto group = std::prev(std::end(groups_));
        assert(!group->entries.empty());
        const auto entry = std::prev(std::end(group->entries));

        map_.erase(entry->key);
        entry->key = key;
        entry->value = value;
        reuse(entry);
        map_.emplace(key, entry);
    }
    else assert(map_.empty());
}

inline LFUCache::Entry::Entry(const std::list<Group>::iterator group,
                              const int key, const int value) noexcept
        : group{group}, key{key}, value{value}
{
}

inline LFUCache::Group::Group(const unsigned frequency) noexcept
        : frequency{frequency}
{
}

constexpr int LFUCache::not_found;

void LFUCache::move_to_group(std::list<Entry>::iterator entry,
                             std::list<Group>::iterator group) noexcept
{
    const auto old_group = entry->group;
    entry->group = group;
    auto& entries = group->entries;
    entries.splice(std::begin(entries), old_group->entries, entry);
}

void LFUCache::bump(const std::list<Entry>::iterator entry)
{
    const auto cur = entry->group;

    if (cur != std::begin(groups_)
                && std::prev(cur)->frequency == cur->frequency + 1u) {
        // A group exists for the higher frequency, so splice the entry there.
        move_to_group(entry, std::prev(cur));
        if (cur->entries.empty()) groups_.erase(cur);
    }
    else if (cur->entries.size() == 1u) {
        // The current group has only this entry, so promote its frequency.
        ++cur->frequency;
    } else {
        // Create a group for the higher frequency, then splice the entry there.
        move_to_group(entry, groups_.emplace(cur, cur->frequency + 1u));
    }
}

void LFUCache::reuse(const std::list<Entry>::iterator entry)
{
    const auto cur = entry->group;
    assert(cur == std::prev(std::end(groups_))); // only reuse from last group

    if (cur->frequency == 1u) {
        // The entry is in the once-group; just put it in the priority position.
        cur->entries.splice(std::begin(cur->entries), cur->entries, entry);
    }
    else if (cur->entries.size() == 1u) {
        // The current group has only this entry, so make it the once-group.
        cur->frequency = 1;
    } else {
        // Create a separate once-group, then splice the entry there.
        groups_.emplace_back(1u);
        const auto next = std::prev(std::end(groups_));
        assert(std::next(cur) == next);
        move_to_group(entry, next);
    }
}

auto LFUCache::make(const int key, const int value)
        -> std::list<Entry>::iterator
{
    // If there is no once-group, create it.
    if (groups_.empty() || groups_.back().frequency != 1u)
        groups_.emplace_back(1u);

    // Construct the new entry in the priority position of the once-group.
    const auto group = std::prev(std::end(groups_));
    group->entries.emplace_front(group, key, value);
    return std::begin(group->entries);
}

namespace {
    void test_very_simple()
    {
        LFUCache cache {10};

        cache.put(10, 100);
        std::cout << cache.get(10) << "\n\n";
    }

    void test_lc_example_ops()
    {
        LFUCache cache {2};

        cache.put(1, 1);
        cache.put(2, 2);
        std::cout << cache.get(1) << '\n';
        cache.put(3, 3);
        std::cout << cache.get(2) << '\n';
        std::cout << cache.get(3) << '\n';
        cache.put(4, 4);
        std::cout << cache.get(1) << '\n';
        std::cout << cache.get(3) << '\n';
        std::cout << cache.get(4) << "\n\n";
    }

    void test_more_ops()
    {
        LFUCache cache {4};

        cache.put(10, 100);
        cache.put(20, 200);
        cache.put(10, 110);
        cache.put(30, 300);
        cache.put(10, 111);
        cache.put(40, 400);
        cache.put(20, 220);
        cache.put(50, 500);
        std::cout << cache.get(5) << '\n';
        std::cout << cache.get(10) << '\n';
        std::cout << cache.get(20) << '\n';
        std::cout << cache.get(30) << '\n';
        std::cout << cache.get(40) << '\n';
        std::cout << cache.get(50) << '\n';
    }
}

int main()
{
    test_very_simple();
    test_lc_example_ops();
    test_more_ops();
}
