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
    static TreeNode* insertIntoBST(TreeNode* root, int val);
};

namespace {
    TreeNode*& insertionPoint(TreeNode*& root, const int val) noexcept
    {
        if (!root) return root;
        
        for (auto parent = root; ; ) {
            auto& child = (val < parent->val ? parent->left : parent->right);
            if (!child) return child;
            parent = child;
        }
    }
}

TreeNode* Solution::insertIntoBST(TreeNode* root, const int val)
{
    insertionPoint(root, val) = new TreeNode{val};
    return root;
}
