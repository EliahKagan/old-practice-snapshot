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
    static ListNode* insertionSortList(ListNode* head) noexcept;
};

ListNode* Solution::insertionSortList(ListNode* head) noexcept
{
    ListNode dest_sentinel {0};

    while (head) {
        auto dest = &dest_sentinel;
        while (dest->next && dest->next->val < head->val) dest = dest->next;

        auto next = head->next;
        head->next = dest->next;
        dest->next = head;

        head = next;
    }

    return dest_sentinel.next;
}
