#include <cstddef>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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

namespace {
    void printInorder(const TreeNode* const root)
    {
        if (root != nullptr) {
            printInorder(root->left);
            cout << root->val << ' ';
            printInorder(root->right);
        }
    }

    void printLevelOrder(const TreeNode* root)
    {
        queue<const TreeNode*> q;
        for (q.push(root); !q.empty(); ) {
            root = q.front();
            q.pop();

            if (root != nullptr) {
                cout << root->val << ' ';
                q.push(root->left);
                q.push(root->right);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout << boolalpha;

    deque<TreeNode> nodes;
    for (auto i = 0; i != 9; ++i) nodes.emplace_back(i);

    nodes[3].left = &nodes[5];
    nodes[3].right = &nodes[1];
    nodes[5].left = &nodes[6];
    nodes[5].right = &nodes[2];
    nodes[1].left = &nodes[0];
    nodes[1].right = &nodes[8];
    nodes[2].left = &nodes[7];
    nodes[2].right = &nodes[4];

    const auto root = &nodes[3];

    printInorder(root);
    cout << '\n';
    printLevelOrder(root);
    cout << "\n\n";

    Solution s;
    cout << s.lowestCommonAncestor(root, &nodes[5], &nodes[1])->val << '\n';
    cout << s.lowestCommonAncestor(root, &nodes[5], &nodes[4])->val << '\n';
    cout << s.lowestCommonAncestor(root, &nodes[6], &nodes[7])->val << '\n';
    cout << s.lowestCommonAncestor(root, &nodes[8], &nodes[8])->val << '\n';
    cout << s.lowestCommonAncestor(root, &nodes[8], &nodes[0])->val << '\n';

    cout << !s.lowestCommonAncestor(&nodes[5], &nodes[2], &nodes[1]) << '\n';
}
