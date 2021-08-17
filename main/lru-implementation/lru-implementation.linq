<Query Kind="Program" />

internal sealed class LRU<TKey> : IEnumerable<TKey> where TKey : struct {
    private sealed class Node {
        public Node Prev, Next;

        public TKey Key;

        public Node(TKey key, Node prev = null, Node next = null)
        {
            Key = key;
            Prev = prev;
            Next = next;
        }
    }

    public readonly int Capacity;

    private Node head = null, tail = null;

    private Dictionary<TKey, Node> lookup = new Dictionary<TKey, Node>();

    public LRU(int capacity)
    {
        if (capacity <= 0) {
            throw new ArgumentOutOfRangeException(
                    "cache capacity must be strictly positive");
        }

        Capacity = capacity;
    }

    public bool Add(TKey key) // true if added, false if already present
    {
        try {
            Node node;
            if (lookup.TryGetValue(key, out node)) {
                MoveToHead(node);
                return false;
            }
    
            var count = lookup.Count;
            if (count == 0) head = tail = new Node(key);
            else if (count < Capacity) {
                head.Prev = new Node(key, null, head);
                head = head.Prev;
            } else {
                lookup.Remove(tail.Key);
                tail.Key = key;
                MoveToHead(tail);
            }
    
            lookup.Add(key, head);
            return true;
        }
        finally {
            lookup.Dump();
        }
    }

    private void MoveToHead(Node node)
    {
        if (node.Prev == null) return; // already at head

        // remove node from its current position in the list
        node.Prev.Next = node.Next;
        if (node.Next == null) tail = node.Prev;
        else node.Next.Prev = node.Prev;

        // re-add node at the head of the list
        node.Prev = null;
        node.Next = head;
        head.Prev = node;
        head = node;
    }

    public IEnumerator<TKey> GetEnumerator()
    {
        for (var node = head; node != null; node = node.Next)
            yield return node.Key;
    }

    IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
}

internal static class LRUEx {
    // Adds keys in order to LRU and return the count of new adds ("faults").
    public static int Add<TKey>(this LRU<TKey> self, IEnumerable<TKey> keys)
            where TKey : struct => keys.Count(self.Add);
}

internal static class Solution {
    private static IEnumerable<int> ReadRecord()
            => Console.ReadLine().Split(' ').Select(int.Parse);

    private static void Main()
    {
        var cache = new LRU<int>(ReadRecord().Last()); // get n, s; use only s
        Console.WriteLine(cache.Add(ReadRecord())); // populate, count faults
        Console.WriteLine(string.Join(" ", cache)); // print cache contents
    }
}
