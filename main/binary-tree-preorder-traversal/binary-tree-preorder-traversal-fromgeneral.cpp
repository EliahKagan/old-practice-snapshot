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
    template<typename FPre, typename FIn, typename FPost>
    void traverse(const TreeNode* root, FPre f_pre, FIn f_in, FPost f_post)
    {
        stack<const TreeNode*> nodes;
        const TreeNode* post {};
        
        while (root || !nodes.empty()) {
            // Go left as far as possbile, doing the preorder action.
            for (; root; root = root->left) {
                f_pre(root->val);
                nodes.push(root);
            }
            
            const auto cur = nodes.top();
            
            if (!cur->right || cur->right != post) {
                // We just came from the left subtree. Do the inorder action.
                f_in(cur->val);
            }
            
            if (cur->right && cur->right != post) {
                // We can visit the right subtree but haven't. Do that.
                root = cur->right;
            } else {
                // Retreat and do the postorder action.
                post = cur;
                nodes.pop();
                f_post(post->val);
            }
        }
    }
    
    constexpr auto noop = [](auto) noexcept { };
}

vector<int> Solution::preorderTraversal(const TreeNode* root)
{
    vector<int> ret;
    traverse(root, [&ret](const auto val) { ret.push_back(val); }, noop, noop);
    return ret;
}
