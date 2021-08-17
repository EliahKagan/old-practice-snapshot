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
    vector<int> inorderTraversal(const TreeNode* root);
};

namespace {
    enum class Action {
        go_left,
        go_right,
        retreat
    };
    
    struct Frame {
        const TreeNode* node;
        Action action;
    };
    
    template<typename FPre, typename FIn, typename FPost>
    void traverse(const TreeNode* const root,
                  FPre f_pre, FIn f_in, FPost f_post)
    {
        stack<Frame> frames;
        frames.push({root, Action::go_left});
        
        while (!empty(frames)) {
            auto& [node, action] = frames.top();
            
            switch (action) {
            case Action::go_left:
                if (!node) goto pop;

                f_pre(node->val);
                action = Action::go_right;
                frames.push({node->left, Action::go_left});
                break;

            case Action::go_right:
                f_in(node->val);
                action = Action::retreat;
                frames.push({node->right, Action::go_left});
                break;

            case Action::retreat:
                f_post(node->val);
            pop:
                frames.pop();
                break;
            }
        }
    }
    
    constexpr auto noop = [](auto) noexcept { };
}

vector<int> Solution::inorderTraversal(const TreeNode* const root)
{
    vector<int> ret;
    traverse(root, noop, [&ret](const auto val) { ret.push_back(val); }, noop);
    return ret;
}
