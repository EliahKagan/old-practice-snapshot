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
    static ListNode* sortList(ListNode* head) noexcept;
};

namespace {
    pair<ListNode*, ListNode*> merge(ListNode* first,
                                     ListNode* second) noexcept
    {
        ListNode sentinel {0};
        auto cur = &sentinel;

        for (; first && second; cur = cur->next) {
            if (second->val < first->val) {
                cur->next = second;
                second = second->next;
            } else {
                cur->next = first;
                first = first->next;
            }
        }

        cur->next = (first ? first : second);
        while (cur->next) cur = cur->next;

        return {sentinel.next, cur};
    }

    inline ListNode* advance(ListNode* node, unsigned distance) noexcept
    {
        while (node && distance--) node = node->next;
        return node;
    }

    ListNode* mergePass(ListNode* const head, const unsigned length) noexcept
    {
        assert(length != 0u);

        ListNode sentinel {0};
        sentinel.next = head;
        auto beforeFirst = &sentinel;

        for (; ; ) {
            const auto beforeSecond = advance(beforeFirst, length);
            const auto second = advance(beforeSecond, 1u);
            if (!second) break; // no more second halves to merge so we're done
            beforeSecond->next = nullptr;

            const auto beforeThird = advance(second, length - 1u);
            const auto third = advance(beforeThird, 1u);
            if (third) beforeThird->next = nullptr;

            ListNode* last {};
            tie(beforeFirst->next, last) = merge(beforeFirst->next, second);
            last->next = third;

            beforeFirst = last;
        }

        return beforeFirst == &sentinel ? nullptr : sentinel.next;
    }
}

ListNode* Solution::sortList(ListNode* head) noexcept
{
    for (auto length = 1u; ; length *= 2u) {
        const auto newHead = mergePass(head, length);
        if (!newHead) return head;
        head = newHead;
    }
}
