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
    static int findBottomLeftValue(const TreeNode* root);
};

int Solution::findBottomLeftValue(const TreeNode* root)
{
    queue<const TreeNode*> q;
    for (q.push(root); !q.empty(); ) {
        root = q.front();
        q.pop();

        if (root->right != nullptr) q.push(root->right);
        if (root->left != nullptr) q.push(root->left);
    }

    return root->val;
}
