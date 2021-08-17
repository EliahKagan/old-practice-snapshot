/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public void reorderList(ListNode head) {
        faroShuffle(head, reverse(split(head)));
    }

    /** Combines two lists, alternating their nodes. */
    private static ListNode faroShuffle(ListNode first, ListNode second) {
        final ListNode sentinel = new ListNode(0);
        ListNode cur = sentinel;

        while (first != null && second != null) {
            cur = cur.next = first;
            first = first.next;

            cur = cur.next = second;
            second = second.next;
        }

        if (first != null) cur = cur.next = first;
        if (second != null) cur = cur.next = second;
        cur.next = null;

        return sentinel.next;
    }

    /** Reverses a list. @return the new head (which was the last node). */
    private static ListNode reverse(ListNode head) {
        ListNode acc = null;

        while (head != null) {
            final ListNode next = head.next;
            head.next = acc;
            acc = head;
            head = next;
        }

        return acc;
    }

    /** Splits a list in two. @return the head of the second list. */
    private static ListNode split(ListNode head) {
        if (head == null) return null;

        for (int i = (length(head) - 1) / 2; i != 0; --i) head = head.next;
        final ListNode ret = head.next;
        head.next = null;
        return ret;
    }

    /** Counts how many nodes are in a list. */
    private static int length(ListNode head) {
        int len = 0;
        for (; head != null; head = head.next) ++len;
        return len;
    }
}
