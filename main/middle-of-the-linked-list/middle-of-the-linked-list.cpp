/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    static ListNode* middleNode(ListNode* head);
};

ListNode* Solution::middleNode(ListNode* head)
{
    if (!head) return nullptr;
    
    for (auto fast = head->next; fast; ) {
        head = head->next;
        fast = fast->next;
        if (fast) fast = fast->next;
    }
    
    return head;
}
