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
    static vector<int> postorderTraversal(const TreeNode* root);
};

vector<int> Solution::postorderTraversal(const TreeNode* root)
{
    vector<int> ret;
    const TreeNode* last {}; // The most recent node whose value was emitted.
    
    for (stack<const TreeNode*> s; !s.empty() || root; ) {
        // Go left.
        for (; root; root = root->left) s.push(root);
        
        // Go right by one, if we can and haven't already.
        if (const auto right = s.top()->right) {
            if (right != last) {
                root = right;
                continue;
            }
        }
        
        last = s.top();
        s.pop();
        ret.push_back(last->val);
    }
    
    return ret;
}
