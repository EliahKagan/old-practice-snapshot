final class Node {
    // Any "key" and "value" would be fine here.
    static final int SENTINEL_KEY = 0, SENTINEL_VALUE = 0;

    /** Constructs a sentinel node. */
    Node() {
        _prev = _next = this;

        _key = SENTINEL_KEY;
        _value = SENTINEL_VALUE;
    }

    /** Tells if this node is a sentinel. */
    boolean isSentinel() {
        final boolean ret = _next == this;
        assert ret == (_prev == this);
        return ret;
    }

    /** Gets the node before this one. */
    Node prev() { return _prev; }

    /** Gets the node after this one. */
    Node next() { return _next; }

    /** Gets this node's key. */
    int key() { return _key; }

    /** Sets this node's key. */
    void setKey(final int key) { _key = key; }

    /** Gets this node's value */
    int value() { return _value; }

    /** Sets this node's value. */
    void setValue(final int value) { _value = value; }

    /** Creates a new data node and places it as the next node after this.
     *  @return the newly created node. */
    Node createNext(final int key, final int value) {
        final Node other = new Node(key, value);
        attachNext(other);
        return other;
    }

    /** Disconnects other and reconnects it as the next node after this. */
    void spliceNext(final Node other) {
        other.detach();
        attachNext(other);
    }

    /** Constructs a new data node. Does NOT assign _prev and _next. */
    private Node(final int key, final int value) {
        _key = key;
        _value = value;
    }

    /** Disconnects this node from the list. Doe NOT update _prev and _next. */
    private void detach() {
        if (isSentinel()) {
            throw new UnsupportedOperationException(
                    "sentinels cannot be spliced or removed");
        }

        _prev._next = _next;
        _next._prev = _prev;
    }

    /** Assumes other is unattached and attaches it after this. */
    private void attachNext(final Node other) {
        other._prev = this;
        other._next = _next;

        _next._prev = other;
        _next = other;
    }

    private Node _prev, _next;
    private int _key, _value;
}

public class LRUCache {
    static final int NOT_FOUND = -1;

    public LRUCache(final int capacity) {
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
            _map.put(key, _list.createNext(key, value));
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
