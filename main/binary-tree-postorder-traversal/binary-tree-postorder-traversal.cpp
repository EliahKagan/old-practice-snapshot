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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        if (!root) return ret;

        stack<const TreeNode*> in, out;
        in.push(root);

        while (!in.empty()) {
            const auto node = in.top();
            in.pop();

            if (node->left) in.push(node->left);
            if (node->right) in.push(node->right);

            out.push(node);
        }

        for (; !out.empty(); out.pop()) ret.push_back(out.top()->val);
        return ret;
    }
};
