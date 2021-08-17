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
    vector<int> inorderTraversal(const TreeNode* root);
};

vector<int> Solution::inorderTraversal(const TreeNode* root)
{
    vector<int> ret;
    
    stack<const TreeNode*> s;
    
    while (root || !s.empty()) {
        // go left
        for (; root; root = root->left) s.push(root);
        
        ret.push_back(s.top()->val);
        root = s.top()->right;
        s.pop();
    }
    
    return ret;
}
