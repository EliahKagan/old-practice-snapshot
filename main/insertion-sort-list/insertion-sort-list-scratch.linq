<Query Kind="Program" />

public class ListNode {
    public int val;
    public ListNode next;
    public ListNode(int x) { val = x; }
}

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

internal static class UnitTest {
    private static ListNode MakeList(params int[] values) {
        var sentinel = new ListNode(0);
        var cur = sentinel;
        foreach (var val in values) cur = cur.next = new ListNode(val);
        return sentinel.next;
    }
    
    private static IEnumerable<int> Values(this ListNode head) {
        for (; head != null; head = head.next) yield return head.val;
    }
    
    private static void Main() {
        var head = MakeList(1,3,2,3,9,7,-13,46 ,8812,0,0,4,0,-1);
        head.Values().Dump();
        new Solution().InsertionSortList(head).Values().Dump();
    }
}
