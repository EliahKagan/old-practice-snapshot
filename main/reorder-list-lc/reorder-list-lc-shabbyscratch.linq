<Query Kind="Program" />

public class ListNode {
    public int val;
    public ListNode next;
    public ListNode(int x) { val = x; }
}

public class Solution {
    internal static ListNode GetMid(ListNode head) {
        for (var fast = head; fast != null && fast.next != null;
                              fast = fast.next.next)
            head = head.next;
        
        return head;
    }
    
    internal static ListNode GetPreMid(ListNode head) {
        var len = 0;
        for (var node = head; node != null; node = node.next) ++len;
        
        for (len = (len - 1) / 2; len != 0; --len) head = head.next;
        return head;
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
        var head = MakeList(0, 1, 2, 3);
        head.Values().Dump("full");
        Solution.GetMid(head).Values().Dump("mid");
        Solution.GetPreMid(head).Values().Dump("premid");
        
        head = MakeList(0, 1, 2, 3, 4);
        head.Values().Dump("full");
        Solution.GetMid(head).Values().Dump("mid");
        Solution.GetPreMid(head).Values().Dump("premid");
        
        head = null;
        head.Values().Dump("full");
        Solution.GetMid(head).Values().Dump("mid");
        Solution.GetPreMid(head).Values().Dump("premid");
    
        //var head = MakeList(1,3,2,3,9,7,-13,46 ,8812,0,0,4,0,-1);
        //head.Values().Dump();
        //new Solution().InsertionSortList(head).Values().Dump();
    }
}
