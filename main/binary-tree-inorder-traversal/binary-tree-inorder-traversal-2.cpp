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
    static vector<int> inorderTraversal(const TreeNode* root);
};

vector<int> Solution::inorderTraversal(const TreeNode* root)
{
    vector<int> ret;

    for (stack<const TreeNode*> nodes; root || !nodes.empty();
                                       root = root->right) {
        for (; root; root = root->left) nodes.push(root); // traverse left

        root = nodes.top();
        nodes.pop();
        ret.push_back(root->val);
    }

    return ret;
}
