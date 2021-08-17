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
    static TreeNode* searchBST(TreeNode* root, const int val) noexcept;
};

TreeNode* Solution::searchBST(TreeNode* root, const int val) noexcept
{
    while (root && val != root->val)
        root = (val < root->val ? root->left : root->right);

    return root;
}
