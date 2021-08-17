#include <array>
#include <cstddef>
#include <iterator>
#include <utility>

namespace {
    template<typename T, std::size_t N = 128>
    class FixedStack {
    public:
        constexpr bool empty() const noexcept { return pos_ == end(elems_); }
        constexpr void push(T elem) noexcept { *--pos_ = std::move(elem); }
        constexpr void pop() noexcept { ++pos_; }
        constexpr const T& top() const noexcept { return *pos_; }
        constexpr T& top() noexcept { return *pos_; }

    private:
        std::array<T, N> elems_ {};
        typename std::array<T, N>::iterator pos_ {end(elems_)};
    };

    template<typename T>
    struct Node {
        T key;
        Node* left;
        Node* right;
    };

    template<typename T, typename P, typename Q>
    Node(T, P, Q) -> Node<T>;

    // Recursive postorder traversal.
    template<typename T, typename F>
    constexpr void postorder_rec(const Node<T>* const root, F f)
        noexcept(noexcept(f(root->key)))
    {
        if (root) {
            postorder_rec(root->left, f);
            postorder_rec(root->right, f);
            f(root->key);
        }
    }

    // Iterative postorder traversal.
    template<typename T, typename F>
    constexpr void postorder_iter(const Node<T>* root, F f)
        noexcept(noexcept(f(root->key)))
    {
        const Node<T>* last {};
        FixedStack<const Node<T>*> nodes;

        while (root || !std::empty(nodes)) {
            // Go left as far as possible.
            for (; root; root = root->left) nodes.push(root);

            if (const auto cur = nodes.top();
                    cur->right && cur->right != last) {
                // The right subtree is nonempty and not yet visited.
                root = cur->right;
            } else {
                // All nodes in the right subtree have been visited.
                last = cur;
                f(last->key);
                nodes.pop();
            }
        }
    }

    enum class Action : char { go_left, go_right, retreat };

    template<typename T>
    struct Frame {
        const Node<T>* node;
        Action action;
    };

    // Iteratively implemented recursive postorder traversal.
    template<typename T, typename F>
    constexpr void postorder_rec_iter(const Node<T>* const root, F f)
        noexcept(noexcept(f(root->key)))
    {
        if (!root) return;

        FixedStack<Frame<T>> frames;
        frames.push({root, Action::go_left});

        while (!std::empty(frames)) {
            switch (auto& [node, action] = frames.top(); action) {
            case Action::go_left:
                action = Action::go_right;
                if (node->left) frames.push({node->left, Action::go_left});
                break;

            case Action::go_right:
                action = Action::retreat;
                if (node->right) frames.push({node->right, Action::go_left});
                break;

            case Action::retreat:
                f(node->key);
                frames.pop();
                break;
            }
        }
    }

    template<typename Traverser>
    constexpr int test(Traverser traverser) noexcept
    {
        Node a {1, nullptr, nullptr};
        Node b {2, nullptr, nullptr};
        Node c {3, &a, &b};

        Node d {4, nullptr, nullptr};
        Node e {5, nullptr, nullptr};
        Node f {6, &d, &e};

        Node g {7, &c, &f};

        auto path = 0;
        traverser(&g, [&path](const auto key) noexcept {
            path = path * 10 + key;
        });

        return path;
    }
}

int main()
{
    constexpr auto rec_res = test([](const auto root, const auto f) {
        postorder_rec(root, f);
    });

    constexpr auto iter_res = test([](const auto root, const auto f) {
        postorder_iter(root, f);
    });

    constexpr auto rec_iter_res = test([](const auto root, const auto f) {
        postorder_rec_iter(root, f);
    });

    static_assert(rec_res == iter_res && iter_res == rec_iter_res);
    return rec_iter_res;
}
