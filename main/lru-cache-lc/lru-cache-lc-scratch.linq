<Query Kind="Program" />

public class LRUCache {
    public const int NotFound = -1;

    public LRUCache(int capacity) => _capacity = capacity;
    
    public int Get(int key) {
        if (_lookup.TryGetValue(key, out var node)) {
            Bump(node);
            return node.Value.CachedValue;
        }
        else return NotFound;
    }
    
    public void Put(int key, int value) {
        if (_lookup.TryGetValue(key, out var node)) {
            node.Value.CachedValue = value;
            Bump(node);
        }
        else if (_chain.Count == _capacity) {
            node = _chain.Last; // reuse the least recently used node
            _lookup.Remove(node.Value.CachedKey);
            
            node.Value.CachedKey = key;
            node.Value.CachedValue = value;
            Bump(node);
            _lookup.Add(key, node);
        } else {
            Debug.Assert(_chain.Count < _capacity);
            
            _chain.AddFirst(new CachedMapping(key, value));
            _lookup.Add(key, _chain.First);
        }
    }
    
    private void Bump(LinkedListNode<CachedMapping> node) { // splices node to front
        _chain.Remove(node);
        _chain.AddFirst(node);
    }
    
    private readonly LinkedList<CachedMapping> _chain =
            new LinkedList<CachedMapping>();
    
    private readonly Dictionary<int, LinkedListNode<CachedMapping>> _lookup =
            new Dictionary<int, LinkedListNode<CachedMapping>>();
    
    private readonly int _capacity;
    
    private sealed class CachedMapping {
        internal int CachedKey, CachedValue;
        
        internal CachedMapping(int key, int value) {
            CachedKey = key;
            CachedValue = value;
        }
    }
}

private static void Main() {
    var cache = new LRUCache(2);
    cache.Put(1, 1);
    cache.Put(2, 2);
    cache.Get(1).Dump();
    cache.Put(3, 3);
    cache.Get(2).Dump();
    cache.Put(4, 4);
    cache.Get(1).Dump();
    cache.Get(3).Dump();
    cache.Get(4).Dump();
}
