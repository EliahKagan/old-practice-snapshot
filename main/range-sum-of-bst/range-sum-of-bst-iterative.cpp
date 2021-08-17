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
    static int rangeSumBST(const TreeNode* root, int min, int max);
};

int Solution::rangeSumBST(const TreeNode* root, const int min, const int max)
{
    if (!root) return 0;
    
    auto acc = 0;
    stack<const TreeNode*> nodes;
    nodes.push(root);
    
    while (!nodes.empty()) {
        root = nodes.top();
        nodes.pop();
        
        if (min <= root->val && root->val <= max) acc += root->val;
        if (root->val <= max && root->right) nodes.push(root->right);
        if (min <= root->val && root->left) nodes.push(root->left);
    }
    
    return acc;
}
