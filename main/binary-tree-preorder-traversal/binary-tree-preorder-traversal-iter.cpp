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
    vector<int> preorderTraversal(const TreeNode* root);
};

vector<int> Solution::preorderTraversal(const TreeNode* root)
{
    vector<int> ret;
    stack<const TreeNode*> nodes;
    
    while (root || !nodes.empty()) {
        // go left as far as possible
        for (; root; root = root->left) {
            ret.push_back(root->val);
            nodes.push(root);
        }
        
        // go right by one, if we can
        root = nodes.top()->right;
        nodes.pop();
    }
    
    return ret;
}
