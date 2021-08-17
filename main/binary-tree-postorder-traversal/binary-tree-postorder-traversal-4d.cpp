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

vector<int> Solution::postorderTraversal(const TreeNode* const root)
{
    struct Frame {
        constexpr Frame(const TreeNode* const _node,
                        void* const _action = &&go_left) noexcept
            : node{_node}, action{_action} { }

        const TreeNode* node;
        void* action;
    };

    vector<int> ret;

    stack<Frame> frames;
    if (root) frames.push(root);

    while (!frames.empty()) {
        auto& frame = frames.top();
        goto *frame.action;

    go_left:
        frame.action = &&go_right;
        if (frame.node->left) frames.push(frame.node->left);
        continue;

    go_right:
        frame.action = &&retreat;
        if (frame.node->right) frames.push(frame.node->right);
        continue;

    retreat:
        ret.push_back(frame.node->val);
        frames.pop();
    }

    return ret;
}
