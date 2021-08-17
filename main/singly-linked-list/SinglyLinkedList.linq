<Query Kind="Program" />

internal sealed class SinglyLinkedList<T> : IEnumerable<T> {
    internal void AddFront(T value)
    {
        if (IsEmpty)
            _first = _last = new Node(value);
        else
            _first = new Node(value, _first);
    }
    
    internal void AddBack(T value)
    {
        if (IsEmpty) {
            _first = _last = new Node(value);
        } else {
            var next = new Node(value);
            _last.Next = next;
            _last = next;
        }
    }
    
    internal T RemoveFront()
    {
        if (IsEmpty) {
            throw new InvalidOperationException(
                    "an empty linked list has no front element to remove");
        }
        
        var ret = _first.Value;
        _first = _first.Next;
        return ret;
    }
    
    internal bool IsEmpty
    {
        get {
            var ret = _first is null;
            Debug.Assert(ret == (_last is null));
            return ret;
        }
    }
    
    public IEnumerator<T> GetEnumerator()
    {
        for (var pos = _first; !(pos is null); pos = pos.Next)
            yield return pos.Value;
    }
    
    IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();

    private sealed class Node {
        internal Node(T value, Node next = null)
            => (Value, Next) = (value, next);
    
        internal T Value { get; }
        
        internal Node Next { get; set; }
    }
    
    private Node _first = null;
    
    private Node _last = null;
}

internal static class Program {
    private static void Add<T>(this SinglyLinkedList<T> self, T item)
        => self.AddBack(item);

    private static void Main()
    {
        var initiallyEmpty = new SinglyLinkedList<string>();
        initiallyEmpty.Dump(nameof(initiallyEmpty));
        
        try {
            initiallyEmpty.RemoveFront().Dump();
        }
        catch (InvalidOperationException e) {
            e.Dump();
        }
        
        initiallyEmpty.AddFront("bar");
        initiallyEmpty.AddFront("foo");
        initiallyEmpty.Dump(nameof(initiallyEmpty));
    
        var items = new SinglyLinkedList<int> { 10, 20, 30, 40, 50 };
        items.Dump(nameof(items));
        
        items.RemoveFront().Dump();
        items.RemoveFront().Dump();
        
        foreach (var num in new[] { 3, 2, 1 }) items.AddFront(num);
        items.Dump(nameof(items));
    }
}
