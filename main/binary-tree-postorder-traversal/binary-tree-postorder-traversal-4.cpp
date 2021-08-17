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

namespace {
    enum class Action { go_left, go_right, retreat };

    struct Frame {
        explicit constexpr Frame(const TreeNode* const _node) noexcept
            : node {_node}, action {Action::go_left}
        {
        }

        const TreeNode* node;
        Action action;
    };
}

vector<int> Solution::postorderTraversal(const TreeNode* const root)
{
    vector<int> ret;

    stack<Frame> frames;
    if (root) frames.emplace(root);

    while (!frames.empty()) {
        auto& frame = frames.top();

        switch (frame.action) {
        case Action::go_left:
            frame.action = Action::go_right;
            if (frame.node->left) frames.emplace(frame.node->left);
            break;

        case Action::go_right:
            frame.action = Action::retreat;
            if (frame.node->right) frames.emplace(frame.node->right);
            break;

        case Action::retreat:
            ret.push_back(frame.node->val);
            frames.pop();
            break;
        }
    }

    return ret;
}
