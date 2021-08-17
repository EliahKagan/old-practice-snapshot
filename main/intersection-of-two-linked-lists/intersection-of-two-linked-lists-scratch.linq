<Query Kind="Program" />

public class ListNode {
    public int val;
    public ListNode next;
    public ListNode(int x) { val = x; }
    
    internal ListNode(int x, ListNode n) { val = x; next = n; } // for debugging
    
    internal static ListNode Create(int[] xs, ListNode tail = null) { // for debugging
        ListNode acc = tail;
        for (var i = xs.Length; i-- != 0; ) acc = new ListNode(xs[i], acc);
        return acc;
    }
}

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

private static void Main() {
    var s = new Solution();
    
    var c = ListNode.Create(new[] { 100, 200, 300 });
    var a = ListNode.Create(new[] { 1, 2 }, c).Dump("a");
    var b = ListNode.Create(new[] { 10, 20, 30 }, c).Dump("b");
    s.GetIntersectionNode(a, b).Dump("a meets b");
    
    var p = ListNode.Create(new[] { 11, 22 }).Dump("p");
    var q = ListNode.Create(new[] { 111, 222, 333 }).Dump("q");
    s.GetIntersectionNode(p, q).Dump("p meets q");
    
    var r = ListNode.Create(new[] { 1111, 2222 }).Dump("r");
    s.GetIntersectionNode(p, r).Dump("p meets r");
}