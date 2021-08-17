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
    const std::function<int(const TreeNode*)>
    dfs {[&](const TreeNode* const node) {
        if (!node) return 0;

        const auto lh = dfs(node->left), rh = dfs(node->right);
        diameter = std::max(diameter, lh + rh);

        return 1 + std::max(lh, rh);
    }};
    
    dfs(root);
    return diameter;
}
