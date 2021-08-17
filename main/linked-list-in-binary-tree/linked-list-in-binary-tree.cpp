/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    static bool isSubPath(const ListNode* head, const TreeNode* root) noexcept;
};

namespace {
    bool isSubPathAt(const ListNode* const head,
                     const TreeNode* const root) noexcept
    {
        if (!head) return true;
        
        if (!root || head->val != root->val) return false;
        
        return isSubPathAt(head->next, root->left)
                || isSubPathAt(head->next, root->right);
    }
    
    bool hasNonemptySubPath(const ListNode* const head,
                            const TreeNode* const root) noexcept
    {
        if (!root) return false;
        
        return isSubPathAt(head, root)
                || hasNonemptySubPath(head, root->left)
                || hasNonemptySubPath(head, root->right);
    }
}

bool Solution::isSubPath(const ListNode* const head,
                         const TreeNode* const root) noexcept
{
    return !head || hasNonemptySubPath(head, root);
}
