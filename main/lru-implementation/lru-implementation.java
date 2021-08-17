import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.StringJoiner;

abstract class PrintableIterable<E> implements Iterable<E> {
    @Override
    public String toString() {
        final StringJoiner sj = new StringJoiner(" ");
        forEach(elem -> sj.add(elem.toString()));
        return sj.toString();
    }
}

final class Node implements Iterable<Integer> {
    Node(final int key) {
        _prev = _next = this;
        _key = key;
    }

    @Override
    public Iterator<Integer> iterator() { return new Iter(this); }

    Node prev() { return _prev; }

    int key() { return _key; }

    void setKey(final int key) { _key = key; }

    void spliceNext(final Node other) {
        // tell other's old neighbors that other is leaving
        other._next._prev = other._prev;
        other._prev._next = other._next;

        // tell other about its new neighbors
        other._prev = this;
        other._next = _next;

        // tell other's new neighbors that other is arriving
        _next._prev = other;
        _next = other;
    }

    private static final class Iter implements Iterator<Integer> {
        Iter(final Node sentinel) { _current = _sentinel = sentinel; }

        @Override
        public boolean hasNext() { return _current._next != _sentinel; }

        @Override
        public Integer next() {
            if (hasNext()) {
                _current = _current._next;
                return _current._key;
            }

            throw new NoSuchElementException();
        }

        private Node _current, _sentinel;
    }

    private Node _prev, _next;
    private int _key;
}

final class LRU extends PrintableIterable<Integer> {
    LRU(final int capacity) {
        if (capacity <= 0)
            throw new IllegalArgumentException("capacity must be positive");

        _table = new HashMap<>(capacity);
        _capacity = capacity;
    }

    @Override
    public Iterator<Integer> iterator() { return _chain.iterator(); }

    boolean bump(final int key) { // returns true iff a cache miss occurs
        boolean miss = false;
        Node node = _table.get(key);

        if (node == null) {
            miss = true;

            if (_table.size() == _capacity) {
                node = _chain.prev();
                _table.remove(node.key());
                node.setKey(key);
            } else {
                assert _table.size() < _capacity;
                node = new Node(key);
            }

            _table.put(key, node);
        }

        _chain.spliceNext(node);
        return miss;
    }

    private final Map<Integer, Node> _table;
    private final Node _chain = new Node(Integer.MIN_VALUE); // sentinel node
    private final int _capacity;
}

final class Solution {
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            int n = sc.nextInt();
            final LRU cache = new LRU(sc.nextInt());

            int misses = 0;
            while (n-- > 0)
                if (cache.bump(sc.nextInt())) ++misses;

            System.out.println(misses);
            System.out.println(cache);
        }
    }

    private Solution() { throw new AssertionError(); }
}
