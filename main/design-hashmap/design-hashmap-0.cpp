class MyHashMap {
public:
    // Initialize your data structure here.
    MyHashMap();

    // value will always be non-negative.
    void put(int key, int value);

    // Returns the value mappped to by the key, or -1 if there is none.
    int get(int key) const noexcept;

    // Removes the mapping for this key if there is none.
    void remove(int key) noexcept;

private:
    struct Entry {
        int key;
        int value;
    };

    template<typename It>
    static It find_entry(It first, It last, int key) noexcept;

    static constexpr auto not_found = -1; // value to return for an unmapped key
    static constexpr size_t initial_bucket_count {1}; // FIXME: make this bigger
    static constexpr auto max_load_factor = 0.75f;

    explicit MyHashMap(size_t bucket_count);

    size_t next_bucket_count() const noexcept;

    static constexpr int prehash(int key) noexcept;

    int hash(int key) const noexcept;

    float load_factor() const noexcept;

    void insert_unchecked(Entry entry);

    void expand();

    vector<vector<Entry>> buckets_;
    int size_ {};
};

inline MyHashMap::MyHashMap() : MyHashMap{initial_bucket_count}
{
}

void MyHashMap::put(const int key, const int value)
{
    auto& bucket = buckets_[hash(key)];
    const auto p = find_entry(begin(bucket), end(bucket), key);

    if (p != end(bucket)) {
        p->value = value;
    }
    else if (load_factor() < max_load_factor) {
        bucket.push_back({key, value});
        ++size_;
    } else {
        expand();
        insert_unchecked({key, value});
    }
}

int MyHashMap::get(const int key) const noexcept
{
    const auto& bucket = buckets_[hash(key)];
    const auto p = find_entry(cbegin(bucket), cend(bucket), key);
    return p != cend(bucket) ? p->value : not_found;
}

void MyHashMap::remove(const int key) noexcept
{
    auto& bucket = buckets_[hash(key)];
    const auto p = find_entry(begin(bucket), end(bucket), key);
    if (p == end(bucket)) return;

    *p = bucket.back();
    bucket.pop_back();
    --size_;
}

template<typename It>
It MyHashMap::find_entry(const It first, const It last, const int key) noexcept
{
    return find_if(first, last, [key](const auto entry) noexcept {
        return entry.key == key;
    });
}

MyHashMap::MyHashMap(const size_t bucket_count) : buckets_{bucket_count}
{
}

inline size_t MyHashMap::next_bucket_count() const noexcept
{
    return buckets_.size() * 2u;
}

constexpr int MyHashMap::prehash(const int key) noexcept
{
    return key; // TODO: consider using a better-distributed prehash
}

inline int MyHashMap::hash(const int key) const noexcept
{
    return prehash(key) % static_cast<int>(buckets_.size());
}

inline float MyHashMap::load_factor() const noexcept
{
    return static_cast<float>(size_) / static_cast<float>(buckets_.size());
}

inline void MyHashMap::insert_unchecked(const Entry entry)
{
    buckets_[hash(entry.key)].push_back(entry);
    ++size_;
}

void MyHashMap::expand()
{
    MyHashMap other {next_bucket_count()};

    for (const auto& bucket : buckets_)
        for (const auto entry : bucket) other.insert_unchecked(entry);

    *this = move(other);
}


/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap obj = new MyHashMap();
 * obj.put(key,value);
 * int param_2 = obj.get(key);
 * obj.remove(key);
 */
