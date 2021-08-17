#include <cstddef>
#include <functional>
#include <iterator>
#include <limits>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

namespace {
    static constexpr size_t k_hashing_prime {31u};

    struct Key {
        size_t val, left_id, right_id;

        Key(const int val, const size_t left_id, const size_t right_id)
            : val{static_cast<size_t>(val)},
              left_id{left_id}, right_id{right_id} { }
    };

    inline bool operator==(const Key& lhs, const Key& rhs)
    {
        return lhs.val == rhs.val && lhs.left_id == rhs.left_id
                                  && lhs.right_id == rhs.right_id;
    }

    inline bool operator!=(const Key& lhs, const Key& rhs)
    {
        return !(lhs == rhs);
    }
}

namespace std {
    template<>
    struct hash<Key> {
        size_t operator()(const Key& key) const
        {
            return key.val
                 + k_hashing_prime * key.left_id
                 + k_hashing_prime * k_hashing_prime * key.right_id;
        }
    };
}

class Solution {
public:
    static bool isSubtree(const TreeNode* s, const TreeNode* t);
};

bool Solution::isSubtree(const TreeNode* const s, const TreeNode* const t)
{
    static constexpr auto null_id = numeric_limits<size_t>::max();
    static constexpr auto no_id = null_id - 1u;
    unordered_map<Key, size_t> ids;

    const function<size_t(const TreeNode*)>
    create_ids = [&ids, &create_ids](const TreeNode* const root) {
        if (root == nullptr) return null_id;

        const Key key {root->val, create_ids(root->left),
                                  create_ids(root->right)};

        const auto p = ids.find(key);
        if (p != end(ids)) return p->second;

        const auto ret = ids.size();
        ids.emplace(key, ret);
        return ret;
    };

    const function<size_t(const TreeNode*)>
    get_id = [&ids, &get_id](const TreeNode* const root) {
        if (root == nullptr) return null_id;

        const auto left_id = get_id(root->left);
        if (left_id == no_id) return no_id;

        const auto right_id = get_id(root->right);
        if (right_id == no_id) return no_id;

        const auto p = ids.find(Key{root->val, left_id, right_id});
        return p == end(ids) ? no_id : p->second;
    };

    create_ids(s);
    return get_id(t) != no_id;
}

int main()
{
    //
}
