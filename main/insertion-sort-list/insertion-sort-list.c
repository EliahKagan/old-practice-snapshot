/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *insertionSortList(struct ListNode *head) {
    struct ListNode sentinel = {0, NULL};
    
    while (head) {
        // find the insertion point
        struct ListNode* dest = &sentinel;
        while (dest->next && dest->next->val < head->val)
            dest = dest->next;
        
        // insert the node and advance the unsorted head pointer
        struct ListNode* const next = head->next;
        head->next = dest->next;
        dest->next = head;
        head = next;
    }
    
    return sentinel.next;
}
