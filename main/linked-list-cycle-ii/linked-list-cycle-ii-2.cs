/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
    public ListNode DetectCycle(ListNode head) {
        // find the intersection
        var slow = head;
        var fast = head;
        do {
            // if we reach the end, then the list was acyclic
            if (fast == null || fast.next == null) return null;
        }
        while ((fast = fast.next.next) != (slow = slow.next));

        // advance to the beginning of the cycle
        while (head != slow) {
            head = head.next;
            slow = slow.next;
        }

        return head;
    }
}
