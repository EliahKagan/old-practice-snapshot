class MyHashSet {
public:
    MyHashSet();

    void add(int key);

    void remove(int key) noexcept;

    // Tells if the set has the specified element.
    bool contains(int key) const noexcept;

private:
    static constexpr size_t initial_bucket_count {10};
    static constexpr auto max_load_factor = 0.75f;

    explicit MyHashSet(size_t bucket_count);

    size_t next_bucket_count() const noexcept;

    static constexpr int prehash(int key) noexcept;

    int hash(int key) const noexcept;

    float load_factor() const noexcept;

    void add_unchecked(int key);

    void expand();

    vector<vector<int>> buckets_;
    int size_ {};
};

inline MyHashSet::MyHashSet() : MyHashSet{initial_bucket_count}
{
}

void MyHashSet::add(const int key)
{
    auto& bucket = buckets_[hash(key)];
    if (find(cbegin(bucket), cend(bucket), key) != cend(bucket)) return;

    if (load_factor() < max_load_factor) {
        bucket.push_back(key);
        ++size_;
    } else {
        expand();
        add_unchecked(key);
    }
}

void MyHashSet::remove(const int key) noexcept
{
    auto& bucket = buckets_[hash(key)];
    const auto p = find(begin(bucket), end(bucket), key);
    if (p == end(bucket)) return;

    *p = bucket.back();
    bucket.pop_back();
    --size_;
}

bool MyHashSet::contains(const int key) const noexcept
{
    const auto& bucket = buckets_[hash(key)];
    return find(cbegin(bucket), cend(bucket), key) != cend(bucket);
}

MyHashSet::MyHashSet(const size_t bucket_count) : buckets_{bucket_count}
{
}

inline size_t MyHashSet::next_bucket_count() const noexcept
{
    return buckets_.size() * 2u;
}

constexpr int MyHashSet::prehash(const int key) noexcept
{
    return key; // TODO: consider using a better-distributed prehash
}

inline int MyHashSet::hash(const int key) const noexcept
{
    return prehash(key) % static_cast<int>(buckets_.size());
}

inline float MyHashSet::load_factor() const noexcept
{
    return static_cast<float>(size_) / static_cast<float>(buckets_.size());
}

inline void MyHashSet::add_unchecked(const int key)
{
    buckets_[hash(key)].push_back(key);
    ++size_;
}

void MyHashSet::expand()
{
    MyHashSet other {next_bucket_count()};

    for (const auto& bucket : buckets_)
        for (const auto elem : bucket) other.add_unchecked(elem);

    *this = move(other);
}


/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet obj = new MyHashSet();
 * obj.add(key);
 * obj.remove(key);
 * bool param_3 = obj.contains(key);
 */
