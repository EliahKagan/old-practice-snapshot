/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public ListNode[] splitListToParts(ListNode head, final int k) {
        final int len = length(head);       // length of the list
        final int short_sublen = len / k;   // length of each short interval
        final int long_count = len % k;     // number of long intervals

        final ListNode[] ret = new ListNode[k];

        for (int i = 0; i != long_count; ++i) {
            ret[i] = head;
            head = drop(head, short_sublen + 1);
        }

        for (int i = long_count; i != k; ++i) {
            ret[i] = head;
            head = drop(head, short_sublen);
        }

        return ret;
    }

    private static int length(ListNode head) {
        int len = 0;
        for (; head != null; head = head.next) ++len;
        return len;
    }

    private static ListNode drop(ListNode head, int count) {
        final ListNode sentinel = new ListNode(0);
        sentinel.next = head;
        for (head = sentinel; count != 0; --count) head = head.next;

        final ListNode next = head.next;
        head.next = null;
        return next;
    }
}
