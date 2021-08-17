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
    static bool isCompleteTree(const TreeNode* root) noexcept;
};

bool Solution::isCompleteTree(const TreeNode* const root) noexcept
{
    if (!root) return true;
    
    auto got_leaf = false;
    queue<const TreeNode*> q;
    
    for (q.push(root); !q.empty(); ) {
        const auto node = q.front();
        q.pop();
        
        if (!node->left)
            got_leaf = true;
        else if (got_leaf)
            return false;
        else
            q.push(node->left);
        
        if (!node->right)
            got_leaf = true;
        else if (got_leaf)
            return false;
        else
            q.push(node->right);
    }
    
    return true;
}
