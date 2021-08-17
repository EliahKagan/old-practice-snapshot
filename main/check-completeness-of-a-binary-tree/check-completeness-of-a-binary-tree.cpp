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

bool Solution::isCompleteTree(const TreeNode* root) noexcept
{
    queue<const TreeNode*> q;
    
    for (q.push(root); q.front(); q.pop()) {
        q.push(q.front()->left);
        q.push(q.front()->right);
    }
    
    for (; !q.empty(); q.pop())
        if (q.front()) return false;
    
    return true;
}
