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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        static constexpr auto base = 10;

        ListNode sentinel {-1};
        auto acc = 0;
        auto p = &sentinel;

        while (acc != 0 || l1 != nullptr || l2 != nullptr) {
            if (l1 != nullptr) {
                acc += l1->val;
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                acc += l2->val;
                l2 = l2->next;
            }

            p = p->next = new ListNode{acc % base};
            acc /= base;
        }

        return sentinel.next == nullptr ? new ListNode{0} : sentinel.next;
    }
};
