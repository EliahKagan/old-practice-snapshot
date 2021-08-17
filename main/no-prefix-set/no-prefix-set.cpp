#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map> 

namespace {
    class Trie {
    public:
        Trie() = default;
        Trie(const Trie&) = delete;
        Trie(Trie&&) = default;
        Trie& operator=(const Trie&) = delete;
        Trie& operator=(Trie&&) = default;
        ~Trie() = default; // beware: even one long string will smash the stack

        bool insert(const std::string& word);

    private:
        // The standard does not guarantee that a Trie can contain a map to a
        // Trie, and this code does not work with libstdc++ (GCC), but it does
        // appear to work with libc++ (clang) and MSVCRT (MSVC++).
        std::unordered_map<char, Trie> children_;
        bool visited_ {false}, terminal_ {false};
    };

    bool Trie::insert(const std::string& word)
    {
        auto p = this;

        for (const auto ch : word) {
            if (p->terminal_) return false;
            p->visited_ = true;
            p = &p->children_[ch];
        }

        if (p->visited_) return false;
        p->terminal_ = p->visited_ = true;
        return true;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    Trie trie;

    auto n = 0;
    for (std::cin >> n; n > 0; --n) {
        std::string word;
        std::cin >> word;

        if (!trie.insert(word)) {
            std::cout << "BAD SET\n" << word << '\n';
            std::exit(0); // don't unwind the stack
        }
    }

    std::cout << "GOOD SET\n";
    std::exit(0); // don't unwind the stack
}
