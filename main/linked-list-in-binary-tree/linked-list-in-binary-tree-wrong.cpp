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

// This should would be correct if the problem were to find a downward path in
// the tree that contains a subsequence, not required to be contiguous, that
// matches the linked list.
bool Solution::isSubPath(const ListNode* const head,
                         const TreeNode* const root) noexcept
{
    if (!head) return true;
    if (!root) return false;

    if (head->val == root->val) {
        if (isSubPath(head->next, root->left)) return true;
        if (isSubPath(head->next, root->right)) return true;
    }

    return isSubPath(head, root->left) || isSubPath(head, root->right);
}
