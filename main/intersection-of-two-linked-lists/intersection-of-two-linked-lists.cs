/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode GetIntersectionNode(ListNode headA, ListNode headB) {
        var d = Measure(headA) - Measure(headB);

        if (d < 0) { // call the longer list A and the shorter list B
            d = -d;
            Swap(ref headA, ref headB);
        }

        for (; d != 0; --d) headA = headA.next;
        for (; headA != headB; headB = headB.next) headA = headA.next;
        return headA;
    }

    private static int Measure(ListNode head) {
        var len = 0;
        for (; head != null; head = head.next) ++len;
        return len;
    }

    private static void Swap<T>(ref T a, ref T b) {
        var tmp = a;
        a = b;
        b = tmp;
    }
}
