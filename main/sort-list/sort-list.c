/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct range {
    struct ListNode *first, *last;
};

static struct range merge(struct ListNode *first, struct ListNode *second)
{
    struct ListNode sentinel = { 0, NULL }, *cur = &sentinel;

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

    return (struct range) { sentinel.next, cur };
}

static struct ListNode *advance(struct ListNode *node, unsigned distance)
{
    while (node && distance--) node = node->next;
    return node;
}

static struct ListNode *mergePass(struct ListNode *const head,
                                  const unsigned length)
{
    assert(length != 0u);

    struct ListNode sentinel = { 0 , head }, *beforeFirst = &sentinel;

    for (; ; ) {
        struct ListNode *const beforeSecond = advance(beforeFirst, length);
        struct ListNode *const second = advance(beforeSecond, 1u);
        if (!second) break; // no more second halves to merge, so we're done
        beforeSecond->next = NULL;

        struct ListNode *const beforeThird = advance(second, length - 1u);
        struct ListNode *const third = advance(beforeThird, 1u);
        if (third) beforeThird->next = NULL;

        const struct range range = merge(beforeFirst->next, second);
        beforeFirst->next = range.first;
        beforeFirst = range.last;
        beforeFirst->next = third;
    }

    return beforeFirst == &sentinel ? NULL : sentinel.next;
}

struct ListNode* sortList(struct ListNode *head)
{
    for (unsigned length = 1u; ; length *= 2u) {
        struct ListNode *const newHead = mergePass(head, length);
        if (!newHead) return head;
        head = newHead;
    }
}
