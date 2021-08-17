#include <cstddef>
#include <functional>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(const int x) : val{x}, left{nullptr}, right{nullptr} { }
};

namespace {
    constexpr size_t hashing_prime {31u};

    struct Key {
        size_t val, left_id, right_id;
        inline Key(int val, size_t left_id, size_t right_id);
    };

    inline Key::Key(const int val, const size_t left_id, const size_t right_id)
        : val{static_cast<size_t>(val)}, left_id{left_id}, right_id{right_id} {
    }

    inline bool operator==(const Key& lhs, const Key& rhs) {
        return lhs.val == rhs.val && lhs.left_id == rhs.left_id
                                  && lhs.right_id == rhs.right_id;
    }

    inline bool operator!=(const Key& lhs, const Key& rhs) {
        return !(lhs == rhs);
    }
}

namespace std {
    template<>
    struct hash<Key> {
        inline size_t operator()(const Key& key) const;
    };

    inline size_t hash<Key>::operator()(const Key& key) const {
        return hashing_prime * hashing_prime * key.val
             + hashing_prime * key.left_id
             + key.right_id;
    }
}

class Solution {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* const root) {
        unordered_map<Key, size_t> ids; // (val, left id #, right id #) -> id #
        vector<TreeNode*> nodes;        // id # -> a representative subroot
        vector<bool> duped;             // duped[i] is true iff #i is duped

        function<size_t(TreeNode*)> identify = [&](TreeNode* const node) {
            if (node == nullptr) return numeric_limits<size_t>::max();

            const Key key {node->val, identify(node->left),
                                      identify(node->right)};
            const auto p = ids.find(key);
            if (p == ids.end()) {
                const auto i = nodes.size();
                ids.emplace(key, i);
                nodes.push_back(node);
                duped.push_back(false); // not yet duped
                return i;
            } else {
                const auto i = p->second;
                duped[i] = true; // was found, so this dupes it
                return i;
            }
        };

        identify(root);

        const auto size = nodes.size();
        vector<TreeNode*> ret;
        for (size_t i {0u}; i != size; ++i)
            if (duped[i]) ret.push_back(nodes[i]);

        return ret;
    }
};

int main() {
    //
}
