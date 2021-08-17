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
    bool isSubPathAfter(const ListNode* head, const TreeNode* root) noexcept
    {
        stack<tuple<const ListNode*, const TreeNode*>> mappings;
        for (mappings.emplace(head, root); !empty(mappings); ) {
            tie(head, root) = mappings.top();
            mappings.pop();
            
            if (!head->next) return true;
            
            if (root->right && head->next->val == root->right->val)
                mappings.emplace(head->next, root->right);
            
            if (root->left && head->next->val == root->left->val)
                mappings.emplace(head->next, root->left);
        }
        
        return false;
    }
    
    bool hasNonemptySubPath(const ListNode* const head,
                            const TreeNode* root) noexcept
    {
        stack<const TreeNode*> roots;
        for (roots.push(root); !empty(roots); ) {
            root = roots.top();
            roots.pop();
            
            if (head->val == root->val && isSubPathAfter(head, root))
                return true;
            
            if (root->right) roots.push(root->right);
            if (root->left) roots.push(root->left);
        }
        
        return false;
    }
}

bool Solution::isSubPath(const ListNode* const head,
                         const TreeNode* const root) noexcept
{
    return !head || (root && hasNonemptySubPath(head, root));
}
