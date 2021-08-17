<Query Kind="Program" />

public class ListNode {
    public int val;
    public ListNode next;
    public ListNode(int x) {
        val = x;
        next = null;
    }
}

internal static class UnitTest {
    internal static ListNode ToListNodes(this IEnumerable<int> xs, int? cycleTo = null)
    {
        var a = xs.Select(x => new ListNode(x)).ToArray();
        
        if (cycleTo.HasValue && !(0 <= cycleTo && cycleTo < a.Length))
            throw new ArgumentOutOfRangeException(nameof(cycleTo));
             
        if (a.Length == 0) return null;
        
        for (var i = 1; i != a.Length; ++i) a[i - 1].next = a[i];
        if (cycleTo.HasValue) a[a.Length - 1].next = a[cycleTo.Value];
        return a[0];
    }
    
    public static ListNode DetectCycle(this ListNode head) {
        for (var visited = new HashSet<ListNode> { null }; visited.Add(head); )
            head = head.next;
        
        return head;
    }
}

private int test = 0;

private void Test(int length, int? cycleTo = null)
    => Enumerable.Range(0, length)
        .ToListNodes(cycleTo).Dump($"Test #{test} uses LIST:")
        .DetectCycle().Dump($"Test #{test++} found CYCLE:");

private void Main() {
    Test(5, 2);
    Test(5, 1);
    Test(5);
    Test(0);
}
