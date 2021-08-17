/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public ListNode partition(ListNode head, int x) {
        final ListNode lowFront = new ListNode(0), highFront = new ListNode(0);
        ListNode low = lowFront, high = highFront;

        for (; head != null; head = head.next) {
            if (head.val < x) {
                low.next = head;
                low = low.next;
            } else {
                high.next = head;
                high = high.next;
            }
        }

        high.next = null;
        low.next = highFront.next;
        return lowFront.next;
    }
}
