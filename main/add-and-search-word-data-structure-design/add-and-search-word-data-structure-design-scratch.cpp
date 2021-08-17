#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() = default;
    WordDictionary(const WordDictionary&) = delete;
    WordDictionary(WordDictionary&&) = default;
    WordDictionary& operator=(const WordDictionary&) = delete;
    WordDictionary& operator=(WordDictionary&&) = default;
    ~WordDictionary();
    
    /** Adds a word into the data structure. */
    void addWord(string word);
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) const;
    
private:
    using Children = unordered_map<char, WordDictionary>;
    
    unique_ptr<Children> children_ {make_unique<Children>()};
    bool terminal_ {false};
};

WordDictionary::~WordDictionary() {
    if (!children_) return;
    
    queue<unique_ptr<Children>> q;
    for (q.emplace(move(children_)); !q.empty(); q.pop()) {
        for (auto& kv : *q.front()) {
            assert(kv.second.children_);
            q.emplace(move(kv.second.children_));
        }
    }
}

void WordDictionary::addWord(const string word) {
    auto p = this;
    for (const auto ch : word) p = &(*p->children_)[ch];
    p->terminal_ = true;
}

bool WordDictionary::search(const string word) const {
    queue<const WordDictionary*> q;
    q.push(this);
    
    for (const auto ch : word) {
        if (ch == '.') {
            for (auto width = q.size(); width != 0; --width) {
                const auto p = q.front();
                q.pop();
                
                // . means any character, so enqueue all the next level's nodes
                for (const auto& kv : *p->children_) q.push(&kv.second);
            }
        } else {
            for (auto width = q.size(); width != 0; --width) {
                const auto p = q.front();
                q.pop();
                
                // enqueue only the nodes that match ch literally, if any
                const auto it = p->children_->find(ch);
                if (it != p->children_->end()) q.push(&it->second);
            }
        }
        
        if (q.empty()) return false;
    }
    
    // the word matches iff any match of the last letter is terminal
    do {
        if (q.front()->terminal_) return true;
        q.pop();
    }
    while (!q.empty());
    
    return false;
}

namespace {
    void run_tests() {
        WordDictionary trie;

        const auto test = [&trie](auto word, bool show = true) {
            cout << "search(\"" << (show ? word : "<not shown>") << "\") -> \""
                 << trie.search(word) << "\"\n";
        };

        test("");
        test(".");
        test("..");
        test("...");
        cout << '\n';

        trie.addWord("abababababababababababababababababababababababababab");
        trie.addWord("ababababababababababababababababababababababcdcdcdcd");
        test(        "ababababababababababababababababababababa..........d");
        test(        "ababababababababababababababababababababa.........ad");
        cout << '\n';

        string s (500, 'y');
        trie.addWord(s);
        fill(begin(s), end(s), '.');
        test(s);

        s += '.';
        cout << s.size() << '\n';
        test(s);

        s.erase(s.size() - 2, 2);
        cout << s.size() << '\n';
        test(move(s));

        cout << s.size() << '\n';
        test(s);
        cout << '\n';

        string t (50'000, 'z');
        trie.addWord(t);
        test(t, false);
        fill(begin(t), end(t), '.');
        test(t, false);

        t += '.';
        cout << t.size() << '\n';
        test(t, false);

        t.erase(t.size() - 2, 2);
        cout << t.size() << '\n';
        test(move(t), false);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << boolalpha;

    run_tests();
}
