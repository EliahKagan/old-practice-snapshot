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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode*> nodes;
        goto goLeft;

        while (!nodes.empty()) {
            root = nodes.top();
            nodes.pop();
            ret.push_back(root->val);
            root = root->right;
    goLeft:
            for (; root; root = root->left) nodes.push(root);
        }

        return ret;
    }
};
