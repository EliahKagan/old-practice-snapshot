/** A node in a circular doubly-linked list. */
final class Node {
    /** Creates a node suitable for use as a sentinel. */
    Node() { }

    /** Creates a node suitable for use as a data node. */
    Node(final int key, final int value) {
        _key = key;
        _value = value;
    }

    /** Gets the node that comes before this one. */
    Node prev() { return _prev; }

    /** Gets the node that comes after this one. */
    Node next() { return _next; }

    /** Gets the key held by this node. */
    int key() { return _key; }

    /** Changes the key held by this node. */
    void setKey(final int key) { _key = key; }

    /** Gets the value held by this node. */
    int value() { return _value; }

    /** Changes the value held by this node. */
    void setValue(final int value) { _value = value; }

    /** Disconnect this node from its adjacent nodes, if any. */
    void detach() {
        _prev._next = _next;
        _next._prev = _prev;

        _prev = _next = this;
    }

    /** Detach the other node and (re)attach it just after this one. */
    void spliceNext(final Node other) {
        other.detach();

        other._prev = this;
        other._next = _next;

        _next._prev = other;
        _next = other;
    }

    private Node _prev = this, _next = this;

    private int _key, _value;
}

public class LRUCache {
    static final int NOT_FOUND = -1;

    public LRUCache(final int capacity) {
        if (capacity <= 0) {
            throw new IllegalArgumentException(
                    "capacity must be strictly positive");
        }

        _capacity = capacity;
    }

    public int get(final int key) {
        final Node node = _map.get(key);
        if (node == null) return NOT_FOUND;

        _list.spliceNext(node);
        return node.value();
    }

    public void put(final int key, final int value) {
        Node node = _map.get(key);

        if (node != null) {
            node.setValue(value);
            _list.spliceNext(node);
        }
        else if (_size == _capacity) {
            node = _list.prev(); // reuse the least recently used node
            _map.remove(node.key());

            node.setKey(key);
            node.setValue(value);
            _list.spliceNext(node);
            _map.put(key, node);
        } else {
            assert _size < _capacity;

            node = new Node(key, value);
            _list.spliceNext(node);
            _map.put(key, node);
            ++_size;
        }

    }

    private final Node _list = new Node();

    private final Map<Integer, Node> _map = new HashMap<>();

    private final int _capacity;

    private int _size = 0;
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
