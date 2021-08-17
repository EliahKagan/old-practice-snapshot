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
    static TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) noexcept;
};

TreeNode* Solution::mergeTrees(TreeNode* const t1,
                               TreeNode* const t2) noexcept
{
    if (!t1) return t2;
    
    if (t2) {
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
    }
    
    return t1;
}
