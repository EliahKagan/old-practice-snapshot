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
    int pathSum(TreeNode* const root, const int sum) {
        if (root == nullptr) return 0;

        unordered_map<int, int> history {{0, 1}}; // old subtotals
        auto cur = 0; // current subtotal
        auto count = 0; // the number of paths found that add up to the sum

        const function<void(const TreeNode*)>
        dfs = [&](const TreeNode* const node) {
            cur += node->val;
            count += history[cur - sum]; // count prev where cur - prev == sum
            ++history[cur];

            if (node->left != nullptr) dfs(node->left);
            if (node->right != nullptr) dfs(node->right);

            --history[cur];
            cur -= node->val;
        };

        dfs(root);
        return count;
    }
};
