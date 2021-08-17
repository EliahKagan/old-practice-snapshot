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
    static bool flipEquiv(const TreeNode* root1,
                          const TreeNode* root2) noexcept;
};

bool Solution::flipEquiv(const TreeNode* const root1,
                         const TreeNode* const root2) noexcept
{
    if (!root1 || !root2) return !root1 && !root2;
    
    if (root1->val != root2->val) return false;
    
    if (flipEquiv(root1->left, root2->left)
            && flipEquiv(root1->right, root2->right))
        return true;
    
    if (flipEquiv(root1->left, root2->right)
            && flipEquiv(root1->right, root2->left))
        return true;
    
    return false;
}
