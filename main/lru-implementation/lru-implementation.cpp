#include <cstddef>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <utility>

#define FORCE_FULL_INSTANTIATION false // for debugging

namespace {
    template<typename TKey>
    class LRU {
    public:
        class iterator;
        using const_iterator = iterator;

        explicit LRU(const std::size_t capacity) : m_capacity{capacity} { }

        LRU(const LRU&) = delete;
        LRU& operator=(const LRU&) = delete;
        LRU(LRU&& other) { swap(other); }
        inline LRU& operator=(LRU&& rhs);
        ~LRU();

        void swap(LRU& other);

        constexpr std::size_t capacity() const noexcept { return m_capacity; }
        std::size_t size() const noexcept { return m_lookup.size(); }
        bool empty() const noexcept { return m_head == nullptr; }

        const_iterator begin() const noexcept { return iterator{*this}; }
        const_iterator end() const noexcept { return iterator{}; }
        const_iterator cbegin() const noexcept { return begin(); }
        const_iterator cend() const noexcept { return end(); }
        
        const TKey& front() const noexcept { return m_head->key; }
        const TKey& back() const noexcept { return m_tail->key; }

        bool add(const TKey& key); // true if added, false if already present

        template<typename... Keys>
        int add(const TKey& head, Keys... tail); // for debugging purposes

        std::size_t m_capacity;

    private:
        struct Node;

        void move_to_head(Node* node) noexcept;

        Node* m_head {nullptr};
        Node* m_tail {nullptr};
        std::unordered_map<TKey, Node*> m_lookup {};
    };

    template<typename TKey>
    struct LRU<TKey>::Node {
        explicit Node(const TKey& key, Node* const prev = nullptr,
                                       Node* const next = nullptr) noexcept
            : key{key}, prev{prev}, next{next} { }

        TKey key;
        Node* prev;
        Node* next;
    };
    
    template<typename TKey>
    inline LRU<TKey>& LRU<TKey>::operator=(LRU<TKey>&& rhs)
    {
        swap(rhs);
        return *this;
    }

    template<typename TKey>
    LRU<TKey>::~LRU()
    {
        while (m_head != m_tail) {
            m_head = m_head->next;
            delete m_head->prev;
        }

        delete m_head;
        m_head = m_tail = nullptr;
    }

    template<typename TKey>
    void LRU<TKey>::swap(LRU<TKey>& other)
    {
        m_lookup.swap(other.m_lookup); // must come first for exception safety
        std::swap(m_tail, other.m_tail);
        std::swap(m_head, other.m_head);
        std::swap(m_capacity, other.m_capacity);
    }

    template<typename TKey>
    bool LRU<TKey>::add(const TKey& key)
    {
        const auto p = m_lookup.find(key);
        if (p != m_lookup.end()) {
            move_to_head(p->second);
            return false; // the key was already present (cache hit)
        }

        if (empty()) m_head = m_tail = new Node{key};
        else if (size() < capacity()) {
            m_head->prev = new Node{key, nullptr, m_head};
            m_head = m_head->prev;
        } else {
            m_lookup.erase(m_tail->key);
            m_tail->key = key;
            move_to_head(m_tail);
        }

        m_lookup.emplace(key, m_head);
        return true; // the key had to be added (cache miss)
    }

    template<typename TKey>
    template<typename... Keys>
    int LRU<TKey>::add(const TKey& head, Keys... tail)
    {
        return add(head) + add(tail...);
    }

    template<typename TKey>
    void LRU<TKey>::move_to_head(Node* node) noexcept
    {
        if (node->prev == nullptr) return; // already at head

        // remove node from its current position in the list
        node->prev->next = node->next;
        (node->next == nullptr ? m_tail : node->next->prev) = node->prev;

        // re-add node at the head of the list
        node->prev = nullptr;
        node->next = m_head;
        m_head->prev = node;
        m_head = node;
    }

    template<typename TKey>
    class LRU<TKey>::iterator
        : public std::iterator<std::forward_iterator_tag, TKey, std::ptrdiff_t,
                               const TKey*, const TKey&> {
    public:
        constexpr iterator() noexcept : m_cur{nullptr} { }

        explicit iterator(const LRU<TKey>& cache) noexcept
            : m_cur{cache.m_head} { }

        const TKey& operator*() const noexcept { return m_cur->key; }

        inline iterator& operator++() noexcept;
        inline iterator operator++(int) noexcept;

        explicit constexpr operator bool() const noexcept
        {
            return m_cur != nullptr;
        }

        friend constexpr bool operator==(const iterator lhs,
                                         const iterator rhs) noexcept
        {
            return lhs.m_cur == rhs.m_cur;
        }

        friend constexpr bool operator!=(const iterator lhs,
                                         const iterator rhs) noexcept
        {
            return lhs.m_cur != rhs.m_cur;
        }

    private:
        const Node* m_cur;
    };

    template<typename TKey>
    inline typename LRU<TKey>::iterator&
    LRU<TKey>::iterator::operator++() noexcept
    {
        m_cur = m_cur->next;
        return *this;
    }

    template<typename TKey>
    inline typename LRU<TKey>::iterator
    LRU<TKey>::iterator::operator++(int) noexcept
    {
        auto ret = *this;
        ++*this;
        return ret;
    }

    template<typename TKey>
    inline void swap(LRU<TKey>& lhs, LRU<TKey>& rhs)
    {
        lhs.swap(rhs);
    }

    template<typename TKey>
    std::ostream& operator<<(std::ostream& out, const LRU<TKey>& cache)
    {
        auto sep = "";
        for (const auto& elem : cache) {
            std::cout << sep << elem;
            sep = " ";
        }

        return out;
    }

#if FORCE_FULL_INSTANTIATION
    template class LRU<int>;
    template void swap(LRU<int>&, LRU<int>&);
    template std::ostream& operator<<(std::ostream&, const LRU<int>&);
#endif
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::size_t count {}, capacity {};
    std::cin >> count >> capacity;
    LRU<int> cache {capacity};
    
    auto misses = 0;
    for (auto elem = 0; count != 0u; --count) {
        std::cin >> elem;
        if (cache.add(elem)) ++misses;
    }

    std::cout << misses << '\n' << cache << '\n';
}
