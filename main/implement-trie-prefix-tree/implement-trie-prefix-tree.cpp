class Trie {
public:
    // Initialize your data structure here.
    Trie() = default;
    Trie(const Trie&) = delete;
    Trie(Trie&&) = default;
    Trie& operator=(Trie&) = delete;
    Trie& operator=(Trie&&) = default;
    ~Trie();

    // Inserts a word into the trie. (Basic exception guarantee only.)
    void insert(string word);

    // Checks if the word is in the trie.
    bool search(string word) const;

    // Checks if any word in the trie starts with the given prefix.
    bool startsWith(string prefix) const;

private:
    using Children = array<Trie, 'z' - 'a' + 1>;

    static size_t idx(const char ch) { return static_cast<size_t>(ch - 'a'); }

    const Trie* findNode(const string& text) const;

    unique_ptr<Children> children_ {};
    bool endsWord_ {false};
};

Trie::~Trie() {
    if (!children_) return;

    queue<unique_ptr<Children>> q;
    for (q.emplace(move(children_)); !q.empty(); q.pop()) {
        for (auto& node : *q.front())
            if (node.children_) q.emplace(move(node.children_));
    }
}

void Trie::insert(const string word) {
    auto p = this;

    for (const auto ch : word) {
        if (!p->children_) p->children_ = make_unique<Children>();
        p = &p->children_->at(idx(ch));
    }

    p->endsWord_ = true;
}

bool Trie::search(const string word) const {
    const auto p = findNode(word);
    return p != nullptr && p->endsWord_;
}

bool Trie::startsWith(const string prefix) const {
    const auto p = findNode(prefix);
    return p != nullptr && (p->children_ || p->endsWord_);
}

const Trie* Trie::findNode(const string& text) const {
    auto p = this;

    for (const auto ch : text) {
        if (!p->children_) return nullptr;
        p = &p->children_->at(idx(ch));
    }

    return p;
}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */
