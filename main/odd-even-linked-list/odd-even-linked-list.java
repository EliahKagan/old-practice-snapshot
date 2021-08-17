/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public ListNode oddEvenList(ListNode head) {
        final ListNode oddFront = new ListNode(0), evenFront = new ListNode(0);
        ListNode odd = oddFront, even = evenFront;

        while (head != null) {
            odd.next = head;
            odd = odd.next;
            head = head.next;

            if (head == null) break;

            even.next = head;
            even = even.next;
            head = head.next;
        }

        even.next = null;
        odd.next = evenFront.next;
        return oddFront.next;
    }
}
