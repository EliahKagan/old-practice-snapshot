/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public ListNode insertionSortList(ListNode head) {
        final ListNode destSentinel = new ListNode(0);

        while (head != null) {
            ListNode dest = destSentinel;
            while (dest.next != null && dest.next.val < head.val)
                dest = dest.next;

            final ListNode next = head.next;
            head.next = dest.next;
            dest.next = head;

            head = next;
        }

        return destSentinel.next;
    }
}
