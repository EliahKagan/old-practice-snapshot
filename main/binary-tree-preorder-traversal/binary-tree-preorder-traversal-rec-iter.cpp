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
    vector<int> preorderTraversal(const TreeNode* root);
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
}

vector<int> Solution::preorderTraversal(const TreeNode* const root)
{
    vector<int> ret;
    if (!root) return ret;
    
    stack<Frame> frames;
    frames.push({root, Action::go_left});
    
    while (!frames.empty()) {
        auto& frame = frames.top();
        
        switch (frame.action) {
        case Action::go_left:
            frame.action = Action::go_right;
            ret.push_back(frame.node->val);
            if (frame.node->left)
                frames.push({frame.node->left, Action::go_left});
            break;

        case Action::go_right:
            frame.action = Action::retreat;
            if (frame.node->right)
                frames.push({frame.node->right, Action::go_left});
            break;

        case Action::retreat:
            frames.pop();
            break;
        }
    }
    
    return ret;
}
