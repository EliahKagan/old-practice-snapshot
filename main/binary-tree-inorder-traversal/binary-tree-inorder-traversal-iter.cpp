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
    stack<const TreeNode*> nodes;
    
    while (root || !nodes.empty()) {
        // go left as far as possible
        for (; root; root = root->left) nodes.push(root);
        
        const auto cur = nodes.top();
        
        // use the value at the current node
        ret.push_back(cur->val);
        
        // go right if possible
        root = cur->right;
        
        nodes.pop();
    }
    
    return ret;
}
