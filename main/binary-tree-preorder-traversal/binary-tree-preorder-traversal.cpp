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
    static vector<int> preorderTraversal(const TreeNode* root);
};

vector<int> Solution::preorderTraversal(const TreeNode* root)
{
    vector<int> ret;
    
    stack<const TreeNode*> s;
    s.push(root);
    
    while (!s.empty()) {
        root = s.top();
        s.pop();
        
        if (!root) continue;
        
        ret.push_back(root->val);
        
        s.push(root->right);
        s.push(root->left);
    }
    
    return ret;
}
