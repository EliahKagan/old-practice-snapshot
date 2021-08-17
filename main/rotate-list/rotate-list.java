/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public ListNode rotateRight(ListNode head, int k) {
        if (k < 0) throw new IllegalArgumentException("k must be nonnegative");
        if (head == null) return null;

        int len = 1;
        ListNode last = head;
        while (last.next != null) {
            last = last.next;
            ++len;
        }

        k %= len;
        if (k == 0) return head;

        last.next = head;
        for (; k != len; ++k) last = last.next;

        head = last.next;
        last.next = null;
        return head;
    }
}
