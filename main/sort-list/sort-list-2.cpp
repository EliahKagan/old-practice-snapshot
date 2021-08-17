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
    static ListNode* sortList(ListNode* head);
};

namespace {
    tuple<ListNode*, ListNode*> merge(ListNode* left, ListNode* right) noexcept
    {
        ListNode sentinel {0};
        auto dest = &sentinel;

        for (; left && right; dest = dest->next) {
            if (right->val < left->val) {
                dest->next = right;
                right = right->next;
            } else {
                dest->next = left;
                left = left->next;
            }
        }

        dest->next = (left ? left : right);
        while (dest->next) dest = dest->next;
        return std::make_tuple(sentinel.next, dest);
    }

    ListNode* walk(ListNode* node, int len) noexcept
    {
		assert(node);
        while (len-- > 0 && node->next) node = node->next;
        return node;
    }

    bool merge_pass(ListNode& sentinel, const int len) noexcept
    {
        for (auto pre_left = &sentinel; ; ) {
            auto pre_right = walk(pre_left, len);
            auto pre_after = walk(pre_right, len);
            if (pre_right == pre_after) return pre_left != &sentinel;

            const auto right = exchange(pre_right->next, nullptr);
            const auto after = exchange(pre_after->next, nullptr);

            tie(pre_left->next, pre_after) = merge(pre_left->next, right);
            pre_after->next = after;
			pre_left = pre_after;
        }
    }
}

ListNode* Solution::sortList(ListNode* const head)
{
    ListNode sentinel {0};
    sentinel.next = head;
    for (auto len = 1; merge_pass(sentinel, len); len *= 2) { }
    return sentinel.next;
}
