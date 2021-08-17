<Query Kind="Program" />

internal sealed class Node<T> {
    public Node(T data = default(T), Node<T> next = null)
    {
        Data = data;
        Next = next;
    }
    
    public Node(params T[] items)
    {
        var head = items.ToNodes();
        Data = head.Data;
        Next = head.Next;
    }

    public T Data { get; set; }
    
    public Node<T> Next { get; set; }
}

internal static class NodeEx {
    public static Node<T> InsertNext<T>(this Node<T> prev, T value)
    {
        return prev == null ? new Node<T>(value)
                            : prev.Next = new Node<T>(value, prev.Next);
    }
    
    public static Node<T> RemoveNext<T>(this Node<T> prev)
    {
        if (prev == null) {
            throw new InvalidOperationException(
                    "null has no next node (it represents an empty list)");
        }
        
        var next = prev.Next;
        
        if (next == null) {
            throw new InvalidOperationException(
                    "no next node to remove (this is the back node)");
        }
        
        prev.Next = next.Next;
        next.Next = null;
        return next;
    }

    public static IEnumerable<T> Traverse<T>(this Node<T> head)
    {
        for (; head != null; head = head.Next) yield return head.Data;
    }
    
    public static Node<T> ToNodes<T>(this IEnumerable<T> items)
    {
        var dummy = new Node<T>();
        var back = dummy;
        
        foreach (var x in items) {
            back.Next = new Node<T>(x);
            back = back.Next;
        }
        
        return dummy.Next;
    }
    
    public static Node<T> ToNodesBack<T>(this IEnumerable<T> items)
    {
        Node<T> head = null;
        foreach (var x in items) head = new Node<T>(x, head);
        return head;
    }
}

internal static class UnitTest {
    private static void Main()
    {
        var head = new Node<string>("foo", "bar", "baz", "quux");
        head.Dump();
        
        var node = new[] { 10, 20, 30, 40, 50 }.ToNodes();
        node.Next.RemoveNext().Dump();
        node.Traverse().Dump();
    }
}
