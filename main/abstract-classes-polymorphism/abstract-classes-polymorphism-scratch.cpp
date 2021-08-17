class LRUCache : public Cache {
public:
    LRUCache(const int capacity)
    {
        assert(capacity > 0);
        cp = capacity;
        head = tail = nullptr;
    }
    
    LRUCache(const LRUCache&) = delete;
    LRUCache(LRUCache&&) = delete;
    
    LRUCache& operator=(const LRUCache&) = delete;
    LRUCache& operator=(LRUCache&&) = delete;
    
    virtual ~LRUCache();
    
    void set(int key, int value) override;
    int get(int key) override;
    
    static constexpr int element_not_found() { return -1; }
    
private:
    void move_to_head(Node* node);
    
    void assign_and_move_to_head(Node* const node, const int value)
    {
        node->value = value;
        move_to_head(node);
    }
};

LRUCache::~LRUCache()
{
    while (head != nullptr) {
        head = head->next;
        delete head->prev;
    }
    
    
    if (head == nullptr) return;
    
    do {
        
    }
    while (head != nullptr);
}

void LRUCache::set(const int key, const int value)
{
    const auto entp = mp.find(key);
    
    if (entp != mp.end()) {
        assign_and_move_to_head(entp->second, value);
        return;
    }
    
    if (mp.empty()) head = tail = new Node(key, value);
    else if (mp.size() < cp) {
        const auto node = new Node(nullptr, head, key, value);
        head = node;
    } else {
        mp.erase(tail->key);
        assign_and_move_to_head(tail, value);
    }
    
    mp.emplace(key, head);
}

int LRUCache::get(int key)
{
    const auto entp = mp.find(key);
    
    if (entp == mp.end()) return element_not_found();
    
    move_to_head(entp->second);
    return head->value;
}

void LRUCache::move_to_head(Node* const node)
{
    if (node->prev == nullptr) return; // already at head
    
    // remove node from its current position in the list
    node->prev->next = node->next;
    (node->next == nullptr ? tail : node->next->prev) = node->prev;
    
    // re-add node at the head of the list
    node->prev = nullptr;
    node->next = head;
    head = node;
}
