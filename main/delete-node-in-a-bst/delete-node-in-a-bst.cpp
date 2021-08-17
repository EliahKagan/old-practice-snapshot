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
    static TreeNode* deleteNode(TreeNode* root, int key) noexcept;
};

namespace {
    TreeNode*& find(TreeNode*& root, const int key) noexcept
    {
        if (!root || root->val == key) return root;

        for (auto parent = root; ; ) {
            auto& child = (key < parent->val ? parent->left : parent->right);
            if (!child || child->val == key) return child;
            parent = child;
        }
    }

    TreeNode*& findMin(TreeNode*& root) noexcept
    {
        assert(root);
        if (!root->left) return root;

        auto parent = root;
        while (parent->left->left) parent = parent->left;
        return parent->left;
    }

    TreeNode* extractMin(TreeNode*& root) noexcept
    {
        auto& pos = findMin(root);
        const auto ret = pos;
        pos = ret->right;
        ret->right = nullptr; // makes debugging easier
        return ret;
    }

    void replace(TreeNode*& oldNode, TreeNode* newNode) noexcept
    {
        newNode->left = oldNode->left;
        newNode->right = oldNode->right;
        oldNode->left = oldNode->right = nullptr; // makes debugging easier
        oldNode = newNode;
    }
}

TreeNode* Solution::deleteNode(TreeNode* root, const int key) noexcept
{
    auto& pos = find(root, key);

    if (pos) {
        if (!pos->left)
            pos = pos->right;
        else if (!pos->right)
            pos = pos->left;
        else
            replace(pos, extractMin(pos->right));
    }

    return root;
}
