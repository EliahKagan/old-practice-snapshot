namespace {
    class Node {
    public:
        // Creates a node suitable for use as a sentinel.
        Node() : key_{}, value_{} { }

        // Creates a node suitable for use as a data node.
        Node(const int key, const int value) : key_{key}, value_{value} { }

        // Nodes are accessed by address, so they shouldn't be copied or moved.
        Node(const Node&) = delete;
        Node(Node&&) = delete;
        Node& operator=(const Node&) = delete;
        Node& operator=(Node&&) = delete;

        // When deleted, nodes automatically delete their whole list.
        ~Node();

        // Gets the node that comes before this one.
        Node* prev() { return prev_; }

        // Gets the node that comes after this one.
        Node* next() { return next_; }

        // Gets the key held by this node.
        int key() const { return key_; }

        // Sets the key held by this node.
        void key(const int new_key) { key_ = new_key; }

        // Gets the value held by this node.
        int value() const { return value_; }

        // Sets the value held by this node.
        void value(const int new_value) { value_ = new_value; }

        // Disconnects this node from its adjacent nodes, if any.
        void detach();

        // Detaches the other node and (re)attaches it just after this one.
        void splice_next(Node* other);

    private:
        Node* prev_ {this}, * next_ {this};
        int key_, value_;
    };

    Node::~Node()
    {
        while (next_ != this) {
            const auto next = this->next_;
            next->detach();
            delete next;
        }

        assert(next_ == this && prev_ == this);
    }

    void Node::detach()
    {
        prev_->next_ = next_;
        next_->prev_ = prev_;

        prev_ = next_ = this;
    }

    void Node::splice_next(Node *const other)
    {
        other->detach();

        other->prev_ = this;
        other->next_ = next_;

        next_->prev_ = other;
        next_ = other;
    }
}

class LRUCache {
public:
    static constexpr auto not_found = -1;

    explicit LRUCache(int capacity);

    int get(int key);

    void put(int key, int value);

private:
    Node list_ {};
    unordered_map<int, Node*> map_ {};
    const int capacity_;
    int size_ {0};
};

LRUCache::LRUCache(const int capacity) : capacity_{capacity}
{
    if (capacity <= 0)
        throw invalid_argument{"capacity must be strictly positive"};
}

int LRUCache::get(const int key)
{
    const auto it = map_.find(key);
    if (it == end(map_)) return not_found;

    const auto node = it->second;
    list_.splice_next(node);
    return node->value();
}

void LRUCache::put(const int key, const int value)
{
    const auto it = map_.find(key);

    if (it != end(map_)) {
        const auto node = it->second;
        node->value(value);
        list_.splice_next(node);
    }
    else if (size_ == capacity_) {
        const auto node = list_.prev(); // reuse the least recently used node
        map_.erase(node->key());

        node->key(key);
        node->value(value);
        list_.splice_next(node);
        map_.emplace(key, node);
    } else {
        assert(size_ < capacity_);

        const auto node = new Node{key, value};
        list_.splice_next(node);
        map_.emplace(key, node);
        ++size_;
    }
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
