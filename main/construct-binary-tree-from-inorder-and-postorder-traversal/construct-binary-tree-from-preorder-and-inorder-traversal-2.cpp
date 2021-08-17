/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    static TreeNode* buildTree(const vector<int>& preorder,
                               const vector<int>& inorder);
};

namespace {
    using It = std::vector<int>::const_iterator;

    unordered_map<int, It> invert(It first, const It last)
    {
        unordered_map<int, It> inverse;
        for (; first != last; ++first) inverse.emplace(*first, first);
        return inverse;
    }

    struct Frame {
        constexpr Frame(TreeNode*& node_,
                        const It pre_first_, const It pre_last_,
                        const It in_first_, const It in_last_) noexcept
            : node{node_}, pre_first{pre_first_}, pre_last{pre_last_},
                           in_first{in_first_}, in_last{in_last_} { }

        TreeNode*& node;
        const It pre_first, pre_last, in_first, in_last;
    };
}

TreeNode* Solution::buildTree(const vector<int>& preorder,
                              const vector<int>& inorder)
{
    assert(preorder.size() == inorder.size());
    const auto in_positions = invert(cbegin(inorder), cend(inorder));

    TreeNode* root {};

    stack<Frame> frames;
    frames.emplace(root, cbegin(preorder), cend(preorder),
                         cbegin(inorder), cend(inorder));

    while (!frames.empty()) {
        decltype(auto) node = frames.top().node;
        const auto pre_first = frames.top().pre_first;
        const auto pre_last = frames.top().pre_last;
        const auto in_first = frames.top().in_first;
        const auto in_last = frames.top().in_last;
        frames.pop();

        assert(pre_first <= pre_last);
        assert(pre_last - pre_first == in_last - in_first);
        if (pre_first == pre_last) continue;

        const auto val = *pre_first;
        const auto in_pos = in_positions.at(val);
        assert(in_first <= in_pos && in_pos < in_last);

        const auto left_len = in_pos - in_first;
        const auto left_pre_first = pre_first + 1;
        const auto right_pre_first = left_pre_first + left_len;

        node = new TreeNode{val};
        frames.emplace(node->right, right_pre_first, pre_last,
                                    in_pos + 1, in_last);
        frames.emplace(node->left, left_pre_first, right_pre_first,
                                   in_first, in_pos);
    }

    return root;
}
