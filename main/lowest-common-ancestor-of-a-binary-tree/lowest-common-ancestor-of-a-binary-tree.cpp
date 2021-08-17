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
    static TreeNode* lowestCommonAncestor(TreeNode* root,
                                          TreeNode* p, TreeNode* q);

private:
    static void trimToIntersection(stack<TreeNode*>& path1,
                                   stack<TreeNode*>& path2);
};

TreeNode* Solution::lowestCommonAncestor(TreeNode* const root,
                                         TreeNode* const p, TreeNode* const q)
{
    stack<TreeNode*> path1, path2;

    const function<bool(TreeNode*)>
    dfs {[p, q, &path1, &path2, &dfs](TreeNode* const node) {
        if (node == nullptr) return false;

        path1.push(node);

        if (node == p || node == q) {
            if (path2.empty()) path2 = path1;
            else return true;
        }

        if (dfs(node->left) || dfs(node->right)) return true;

        path1.pop();
        return false;
    }};

    dfs(root);

    if (path1.empty() || path2.empty())
        return p != q || (path1.empty() && path2.empty()) ? nullptr : p;

    trimToIntersection(path1, path2);
    return path1.top();
}

void Solution::trimToIntersection(stack<TreeNode*>& path1,
                                  stack<TreeNode*>& path2)
{
    while (path1.size() > path2.size()) path1.pop();
    while (path1.size() < path2.size()) path2.pop();

    while (path1.top() != path2.top()) {
        path1.pop();
        path2.pop();
    }
}
