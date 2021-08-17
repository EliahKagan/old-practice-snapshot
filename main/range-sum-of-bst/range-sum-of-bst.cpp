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

int Solution::rangeSumBST(const TreeNode* const root,
                          const int min, const int max)
{
    if (!root) return 0;
    
    auto acc = 0;
    if (min <= root->val && root->val <= max) acc += root->val;
    if (min <= root->val) acc += rangeSumBST(root->left, min, max);
    if (root->val <= max) acc += rangeSumBST(root->right, min, max);
    return acc;
}
