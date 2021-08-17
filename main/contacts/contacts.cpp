#include <array>
#include <cstddef>
#include <deque>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

namespace {
    class Trie {
    public:
        Trie();

        void add(std::string::const_iterator first,
                 std::string::const_iterator last);

        void add(const std::string& chain)
        {
            add(std::cbegin(chain), std::cend(chain));
        }

        size_t count(const std::string& prefix) const;

    private:
        class Node {
        public:
            explicit Node(const std::size_t count = 1u) noexcept
                : count_{count} { }

            const Node* at(const char ch) const
            {
                return children_.at(index(ch));
            }

            Node*& at(const char ch)
            {
                return children_.at(index(ch));
            }

            std::size_t count() const noexcept { return count_; }

            void increment_count() noexcept { ++count_; }

        private:
            static constexpr std::size_t index(char ch) noexcept;

            std::array<Node*, 'z' - 'a' + 1u> children_ {};
            std::size_t count_;
        };

        Node* make_node();

        std::deque<Node> nodes_;
    };

    Trie::Trie()
    {
        nodes_.emplace_back(0u);
    }

    void Trie::add(std::string::const_iterator first,
                   const std::string::const_iterator last)
    {
        auto cur = &nodes_.front();
        cur->increment_count();

        for (; first != last; ++first) {
            const auto next = cur->at(*first);
            if (!next) break;
            cur = next;
            cur->increment_count();
        }

        for (; first != last; ++first) {
            const auto next = make_node();
            cur->at(*first) = next;
            cur = next;
        }
    }

    std::size_t Trie::count(const std::string& prefix) const
    {
        auto cur = &nodes_.front();

        for (const auto ch : prefix) {
            cur = cur->at(ch);
            if (!cur) return 0u;
        }

        return cur->count();
    }

    constexpr std::size_t Trie::Node::index(const char ch) noexcept
    {
        return static_cast<std::size_t>(ch) - static_cast<std::size_t>('a');
    }

    auto Trie::make_node() -> Node*
    {
        nodes_.emplace_back();
        return &nodes_.back();
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    Trie trie;

    auto n = 0;
    for (std::cin >> n; n > 0; --n) {
        std::string action, word;
        std::cin >> action >> word;

        if (action == "add") trie.add(word);
        else if (action == "find") std::cout << trie.count(word) << '\n';
        else throw std::invalid_argument{"unrecognized action"};
    }
}
