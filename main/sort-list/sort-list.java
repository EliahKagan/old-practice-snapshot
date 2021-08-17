/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    /** Mergesorts a singly linked list in O(1) extra space (bottom-up).
     * @param head     The head of the list (or null if empty).
     * @return The head of the list, whose nodes are rearranged. */
    public ListNode sortList(ListNode head) {
        for (int length = 1; ; length *= 2) {
            final ListNode newHead = mergePass(head, length);
            if (newHead == null) break;

            head = newHead;
        }

        return head;
    }

    /** Holds the first and last nodes in a list. */
    private static class Range {
        Range(final ListNode first, final ListNode last) {
            this.first = first;
            this.last = last;
        }

        final ListNode first, last;
    }

    /** Merges non-overlapping pairs of sublists of up to a specified length.
     * @param head      The head of the list (or null if empty).
     * @param length    The length of each sublist to merge.
     * @return The head of list of merged nodes, or null if there was no
     *         merging to do because the list had no more than length nodes. */
    private static ListNode mergePass(final ListNode head, final int length) {
        if (length <= 0)
            throw new IllegalArgumentException("length must be positive");

        final ListNode sentinel = new ListNode(0);
        sentinel.next = head;
        ListNode beforeFirst = sentinel;

        for (; ; ) {
            final ListNode beforeSecond = advance(beforeFirst, length);
            final ListNode second = advance(beforeSecond, 1);
            if (second == null) break; // there will be no second half to merge
            beforeSecond.next = null;

            final ListNode beforeThird = advance(second, length - 1);
            final ListNode third = advance(beforeThird, 1);
            if (third != null) beforeThird.next = null;

            final Range range = merge(beforeFirst.next, second);
            beforeFirst.next = range.first;
            beforeFirst = range.last;
            beforeFirst.next = third;
        }

        return beforeFirst == sentinel ? null : sentinel.next;
    }

    /** Advances the list by the specified number of nodes.
     * @param node      The node to start from.
     * @param distance  The number of nodes to advance.
     * @return The node distance nodes after node, or null if there is none. */
    private static ListNode advance(ListNode node, int distance) {
        for (; node != null && distance != 0; --distance) node = node.next;
        return node;
    }

    /** Merges two acyclic non-overlapping singly linked lists, that should
     *  themselves already be sorted and nonempty, in stably sorted order.
     * @param first     The head of the first list.
     * @param second    The head of the second list.
     * @return A pair of the merged list's first and last nodes. */
    private static Range merge(ListNode first, ListNode second) {
        final ListNode sentinel = new ListNode(0);
        ListNode cur = sentinel;

        for (; first != null && second != null; cur = cur.next) {
            if (second.val < first.val) {
                cur.next = second;
                second = second.next;
            } else {
                cur.next = first;
                first = first.next;
            }
        }

        cur.next = (second == null ? first : second);
        while (cur.next != null) cur = cur.next;

        return new Range(sentinel.next, cur);
    }
}
