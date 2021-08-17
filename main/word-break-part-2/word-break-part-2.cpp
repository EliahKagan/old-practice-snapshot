#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>

namespace {
    class Trie {
    public:
        void insert(std::string::const_iterator first,
                    std::string::const_iterator last);
        
    private:
        std::unordered_map<char, Trie> subtries_ {};
        bool complete_ {false}; // the path to this node is a complete word
    };
    
    void Trie::insert(std::string::const_iterator first,
                      std::string::const_iterator last)
    {
        if (first == last) {
            complete_ = true;
            return;
        }
        
        auto p = subtries_.find(*first);
        
        if (p == subtries_.end())
            std::tie(p, std::ignore) = subtries_.emplace(*first, Trie{});
        
        p->second.insert(std::move(++first), std::move(last));
    }
}

int main()
{
    std::cout << "Hello, world!\n";
}
