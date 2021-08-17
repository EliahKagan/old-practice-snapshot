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
    using It = vector<int>::const_iterator;

    unordered_map<int, It> invert(It first, const It last)
    {
        unordered_map<int, It> inverse;
        for (; first != last; ++first) inverse.emplace(*first, first);
        return inverse;
    }
}

TreeNode* Solution::buildTree(const vector<int>& preorder,
                              const vector<int>& inorder)
{
    assert(preorder.size() == inorder.size());
    const auto in_positions = invert(cbegin(inorder), cend(inorder));

    const function<TreeNode*(It, It, It, It)> build = [&in_positions, &build](
                const It pre_first, const It pre_last,
                const It in_first, const It in_last) -> TreeNode* {
        const auto len = pre_last - pre_first;
        if (len == 0) return nullptr;

        assert(len > 0);
        assert(in_last - in_first == len);

        const auto val = *pre_first;
        const auto in_pos = in_positions.at(val);
        assert(in_first <= in_pos && in_pos < in_last);

        const auto left_len = in_pos - in_first;
        const auto left_pre_first = pre_first + 1;
        const auto right_pre_first = left_pre_first + left_len;

        const auto root = new TreeNode{val};
        root->left = build(left_pre_first, right_pre_first,
                           in_first, in_pos);
        root->right = build(right_pre_first, pre_last,
                            in_pos + 1, in_last);
        return root;
    };

    return build(cbegin(preorder), cend(preorder),
                 cbegin(inorder), cend(inorder));
}
