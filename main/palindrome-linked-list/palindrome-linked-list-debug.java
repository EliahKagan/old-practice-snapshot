/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public boolean isPalindrome(ListNode head) {
        if (head == null) return true;

        final ListNode beforeSecond = findMiddle(head);
        ListNode second = beforeSecond.next;
        beforeSecond.next = null;

        second = reverse(second);
        print(head); // FIXME: remove after debugging
        print(second); // FIXME: remove after debugging
        final boolean ret = match(head, second);
        beforeSecond.next = reverse(second);
        return ret;
    }

    private static ListNode findMiddle(ListNode head) {
        for (ListNode fast = head.next; fast != null && fast.next != null;
                                        fast = fast.next.next)
            head = head.next;

        return head;
    }

    private static ListNode reverse(ListNode head) { // returns new head
        ListNode acc = null;

        while (head != null) {
            final ListNode next = head.next;
            head.next = acc;
            acc = head;
            head = next;
        }

        return acc;
    }

    private static boolean match(ListNode first, ListNode second) {
        while (first != null && second != null) {
            System.out.format("Comparing %d to %d.%n", first.val, second.val); // FIXME: remove after debugging
            if (first.val != second.val) return false;

            first = first.next;
            second = second.next;
        }

        return true;
    }

    private static void print(ListNode head) { // FIXME: remove this (and all its calls) after debugging
        System.out.print("[");
        for (; head != null; head = head.next) System.out.print(" " + head.val);
        System.out.println(" ]");
    }
}
