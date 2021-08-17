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
    static int diameterOfBinaryTree(const TreeNode* root);
};

int Solution::diameterOfBinaryTree(const TreeNode* const root)
{
    auto diameter = 0;
    
    // Returns height, updates diameter.
    const auto dfs = [&diameter](const TreeNode* const _root) {
        const auto dfs_impl = [&diameter](const auto self, const auto node) {
            if (!node) return 0;
            
            const auto lh = self(self, node->left);
            const auto rh = self(self, node->right);
            diameter = std::max(diameter, lh + rh);
            
            return 1 + std::max(lh, rh);
        };
        
        dfs_impl(dfs_impl, _root);
    };
    
    dfs(root);
    return diameter;
}
