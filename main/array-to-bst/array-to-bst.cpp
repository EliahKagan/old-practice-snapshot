#include <iostream>
#include <memory>
#include <utility>
#include <vector>

namespace {
    struct Node {
        int key;
        std::unique_ptr<Node> left, right;
    };

    inline std::unique_ptr<Node> make_node(const int key,
                                           std::unique_ptr<Node>&& left,
                                           std::unique_ptr<Node>&& right)
    {
        return std::unique_ptr<Node>{new Node{key, std::move(left),
                                                   std::move(right)}};
    }

    using It = std::vector<int>::const_iterator;

    std::unique_ptr<Node> make_tree(const It first, const It last)
    {
        if (first == last) return nullptr;

        const auto mid = first + (last - first - 1) / 2;

        return make_node(*mid, make_tree(first, mid),
                               make_tree(mid + 1, last));
    }

    template<typename F>
    void traverse_preorder(const std::unique_ptr<Node>& root, const F action)
    {
        if (root) {
            action(root->key);
            traverse_preorder(root->left, action);
            traverse_preorder(root->right, action);
        }
    }

    std::vector<int> read_record()
    {
        std::vector<int>::size_type size {};
        std::cin >> size;

        std::vector<int> a (size);
        for (auto& elem : a) std::cin >> elem;
        return a;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto a = read_record();
        const auto root = make_tree(a.cbegin(), a.cend());

        auto sep = "";
        traverse_preorder(root, [&sep](const int key) {
            std::cout << sep << key;
            sep = " ";
        });

        std::cout << '\n';
    }
}
