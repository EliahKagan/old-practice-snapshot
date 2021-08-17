#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <string>
#include <vector>
using namespace std;

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

namespace {
    void run_tests() {
        Trie trie;

        const auto test = [&trie](auto text, bool show = true) {
            cout << "search(\"" << (show ? text : "...") << "\") -> \""
                 << trie.search(text) << "\"\n";
            cout << "startsWith(\"" << (show ? text : "...") << "\") -> \""
                 << trie.startsWith(text) << "\"\n";
        };

        test("");
        cout << '\n';

        trie.insert("foobar");
        trie.insert("foo");
        trie.insert("quux");

        const vector<const char*> a {
            "", "fo", "foo", "foob", "foobar", "foobard",
            "quu", "quux", "quuxa"
        };

        for_each(cbegin(a), cend(a), test);
        cout << '\n';

        string s (500, 'a');
        trie.insert(s);
        s.resize(s.size() - 1);
        test(move(s));

        string t (1'000'000, 'b');
        trie.insert(t);
        t.resize(t.size() - 1);
        test(move(t), false);

        cout << "\nDone.\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << boolalpha;

    run_tests();
}
