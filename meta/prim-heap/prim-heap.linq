<Query Kind="Program" />

internal sealed class MinHeap<TKey, TValue>
        where TValue : IComparable<TValue> {
    internal int Count => _heap.Count;
    
    internal void Clear()
    {
        _table.Clear();
        _heap.Clear();
    }
    
    internal KeyValuePair<TKey, TValue> Peek()
    {
        if (Count == 0)
            throw new InvalidOperationException(message: "heap empty");
        
        return _heap[0];
    }
    
    internal KeyValuePair<TKey, TValue> Pop()
    {
        var ret = Peek();
        
        if (Count == 1) {
            Clear();
        } else {
            _table.Remove(ret.Key);
            
            var last = Count - 1;
            _heap[0] = _heap[last];
            _heap.RemoveAt(last);
            
            HeapifyDown(0);
        }
        
        return ret;
    }
    
    internal void Push(TKey key, TValue value)
    {
        if (Contains(key)) {
            throw new ArgumentException(message: "key already present",
                                        paramName: nameof(key));
        }
        
        var child = Count;
        _heap.Add(new KeyValuePair<TKey, TValue>(key, value));
        HeapifyUp(child);
    }
    
    internal bool Contains(TKey key) => _table.ContainsKey(key);
    
    internal void Decrease(TKey key, TValue value)
    {
        if (!_table.TryGetValue(key, out var child)) {
            throw new ArgumentException(message: "key not present",
                                        paramName: nameof(key));
        }
        
        if (_heap[child].Value.CompareTo(value) < 0) {
            throw new ArgumentOutOfRangeException(
                    paramName: nameof(value),
                    message: "stored value is lower");
        }
        
        _heap[child] = new KeyValuePair<TKey, TValue>(key, value);
        HeapifyUp(child);
    }
    
    private const int NoChild = -1;
    
    private void HeapifyUp(int child)
    {
        while (child != 0) {
            var parent = (child - 1) / 2;
            if (OrderOk(parent, child)) break;
            
            Swap(child, parent);
            child = parent;
        }
        
        Record(child);
    }
    
    private void HeapifyDown(int parent)
    {
        for (; ; ) {
            var child = PickChild(parent);
            if (child == NoChild || OrderOk(parent, child)) break;
            
            Swap(parent, child);
            parent = child;
        }
        
        Record(parent);
    }
    
    private int PickChild(int parent)
    {
        var left = parent * 2 + 1;
        if (left >= Count) return NoChild;
        
        var right = left + 1;
        return right == Count || OrderOk(left, right) ? left : right;
    }
    
    private bool OrderOk(int parent, int child)
        => _heap[parent].Value.CompareTo(_heap[child].Value) <= 0;
    
    private void Swap(int src, int dest)
    {
        var tmp = _heap[dest];
        _heap[dest] = _heap[src];
        _heap[src] = tmp;
        
        Record(src);
    }
    
    private object ToDump() => new { _table, _heap }; 
    
    private void Record(int index)
        => _table[_heap[index].Key.Dump($"index {index}")] = index;
    
    private readonly Dictionary<TKey, int> _table =
            new Dictionary<TKey, int>();
    
    private readonly List<KeyValuePair<TKey, TValue>> _heap =
            new List<KeyValuePair<TKey, TValue>>();
}

internal static class UnitTest {
    private static void Main()
    {
        var heap = new MinHeap<char, long>();
        
        heap.Push('a', 10);
        heap.Dump();
        heap.Push('b', 90);
        heap.Dump();
        heap.Push('c', 50);
        heap.Dump();
        heap.Push('d', 70);
        heap.Dump();
//#if false
        heap.Push('e', 80);
        heap.Dump();
        heap.Push('f', 60);
        heap.Dump();
        heap.Push('g', 30);
        heap.Dump();
        heap.Push('h', 20);
        heap.Dump();
        heap.Push('i', 40);
        heap.Dump();
        
        while (heap.Count != 0) heap.Pop().Dump();
//#endif
    }
}