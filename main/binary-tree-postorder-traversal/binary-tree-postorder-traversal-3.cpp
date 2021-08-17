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
    vector<int> postorderTraversal(const TreeNode* root);
};

vector<int> Solution::postorderTraversal(const TreeNode* root)
{
    vector<int> ret;
    
    const TreeNode* last {};
    stack<const TreeNode*> s;
    
    while (root || !s.empty()) {
        // Go left as far as possible.
        for (; root; root = root->left) s.push(root);
        
        // Go right from here by one, if we can and haven't already.
        if (const auto right = s.top()->right) {
            if (right != last) {
                root = right;
                continue;
            }
        }
        
        // Use the value here and retreat.
        last = s.top();
        s.pop();
        ret.push_back(last->val);
    }
    
    return ret;
}
