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
    stack<const TreeNode*> nodes;
    const TreeNode* last {};
    
    while (root || !nodes.empty()) {
        // Go left as far as possible.
        for (; root; root = root->left) nodes.push(root);
        
        const auto cur = nodes.top();
        
        if (cur->right && cur->right != last) {
            // We can traverse right but have not yet done so. Go right.
            root = cur->right;
        } else { 
            // We cannot traverse right or have already done so. Retreat.
            ret.push_back(cur->val);
            last = cur;
            nodes.pop();
        }
    }
    
    return ret;
}
