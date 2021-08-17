/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode InsertionSortList(ListNode head) {
        var destSentinel = new ListNode(0);

        while (head != null) {
            var dest = destSentinel;
            while (dest.next != null && dest.next.val < head.val)
                dest = dest.next;

            var next = head.next;
            head.next = dest.next;
            dest.next = head;

            head = next;
        }

        return destSentinel.next;
    }
}
