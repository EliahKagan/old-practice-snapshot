<Query Kind="Program" />

public class ListNode {
    public int val;
    public ListNode next;
    public ListNode(int x) { val = x; }
}

public class Solution {
    /// <summary>Mergesorts a singly linked list. O(1) extra space.</summary>
    /// <param name="head">The head of the list (or null if empty).</param>
    /// <returns>The head of the list, whose nodes are rearranged.</returns>
    public ListNode SortList(ListNode head)
    {
        for (var length = 1; ; length *= 2) {
            var newHead = MergePass(head, length);
            if (newHead == null) break;
            head = newHead;
        }
        
        return head;
    }
    
    /// <summary>Merges pairs of sublists of a specified length.</summary>
    /// <param name="head">The head of the list (or null if empty).</param>
    /// <param name="length">The length of each sublist to merge.</param>
    /// <returns>
    /// The head of list of merged nodes, or <c>null</c> if there was no
    /// merging to do because the list had no more than <c>length</c> nodes.
    /// </returns>
    private static ListNode MergePass(ListNode head, int length)
    {
        EnsureLengthPositive(length);
    
        var sentinel = new ListNode(0);
        sentinel.next = head;
        var beforeFirst = sentinel;
        
        for (; ; ) {
            var beforeSecond = Advance(beforeFirst, length);
            var second = beforeSecond?.next;
            if (second == null) break; // no second sequence to merge with
            beforeSecond.next = null;
            
            var beforeThird = Advance(second, length - 1);
            var third = beforeThird?.next;
            if (third != null) beforeThird.next = null;
            
            var (newFirst, newLast) = Merge(beforeFirst.next, second);
            beforeFirst.next = newFirst;
            newLast.next = third;
            beforeFirst = newLast;
        }
        
        return beforeFirst == sentinel ? null : sentinel.next;
    }
    
    /// <summary>
    /// Merges two acyclic non-overlapping singly linked lists, that should
    /// themselves already be sorted and nonempty, in stably sorted order.
    /// </summary>
    /// <param name="first">The head of the first list.</param>
    /// <param name="second">The head of the second list.</param>
    /// <returns>A pair of the merged list's first and last nodes.</returns>
    private static (ListNode, ListNode) Merge(ListNode first, ListNode second)
    {
        var sentinel = new ListNode(0);
        var cur = sentinel;
        
        for (; first != null && second != null; cur = cur.next) {
            if (second.val < first.val) {
                cur.next = second;
                second = second.next;
            } else {
                cur.next = first;
                first = first.next;
            }
        }
        
        cur.next = (first == null ? second : first);
        while (cur.next != null) cur = cur.next;
        
        return (sentinel.next, cur);
    }
    
    
    /// <summary>Advances in the list by specified number of nodes.</summary>
    /// <param name="node">The node to start from.</param>
    /// <param name="len">The length (number of nodes) to advance.</param>
    /// <returns>
    /// The node <c>len</c> nodes past <c>node</c>, or <c>null</c> if there is
    /// no such node or if <c>node</c> was <c>null</c>.
    /// </returns>
    private static ListNode Advance(ListNode node, int len)
    {
        for (; node != null && len != 0; --len) node = node.next;
        return node;
    }
    
    /// <summary>Throws an exception if <c>length</c> is nonpositive.</summary>
    /// <param name="length">The parameter whose value is checked.</param>
    private static void EnsureLengthPositive(int length)
    {
        if (length <= 0) {
            throw new ArgumentOutOfRangeException(nameof(length),
                    $"{nameof(length)} must be (strictly) positive");
        }
    }
}

internal static class UnitTest {
    private static void Main()
    {
        s_testCount = 0; // needed in LINQPad
        
        Test(true, 10, 20, 30, 40, 50, 60);
        Test(true, 3, 5, 2, 1, 2, 16, 4, 9, 8, 3, 6, 3);
        Test(true, 17);
        Test(true, 34, 17);
        
        foreach (var length in new[] { 10_000_000, 100_000_000 }) {
            var a = new int[length];
            for (var i = 0; i != length; ++i) a[i] = length - i;
            Test(false, a);
        }
        
        var seed = (int)DateTime.Now.Ticks;
        seed.Dump(nameof(seed));
        var gen = new Random(seed);
        
        var b = MakeRandomArray(gen, 25);
        b.Dump(nameof(b));
        Test(true, b);
        
        for (var i = 5; i != 0; --i)
            Test(false, MakeRandomArray(gen, 10_000_000));
        
        for (var i = 2; i != 0; --i)
            Test(false, MakeRandomArray(gen, 100_000_000));
    }
    
    private static void Test(bool display, params int[] values)
    {
        ++s_testCount; 
        
        var head = new Solution().SortList(MakeList(values));
        if (display) head.Dump($"Test #{s_testCount} results:");
        IsSorted(head).Dump($"Test #{s_testCount} is correct?");
    }
    
    private static ListNode MakeList(params int[] values)
    {
        var sentinel = new ListNode(0);
        var cur = sentinel;
        
        foreach (var val in values) {
            cur = cur.next = new ListNode(0);
            cur.val = val;
        }
        
        return sentinel.next;
    }
    
    private static bool IsSorted(ListNode head)
    {
        if (head == null) return true;
        
        while (head.next != null && head.val <= head.next.val)
            head = head.next;
        
        return head.next == null;
    }
    
    private static int[] MakeRandomArray(Random gen, int length)
    {
        var values = new int[length];
        for (var i = 0; i != length; ++i)
            values[i] = gen.Next(int.MinValue, int.MaxValue);
        
        return values;
    }
    
    private static int s_testCount;
}
