import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

/** A modified binary minheap, suitable for Prim's algorithm.
 *  Traditionally one adds contains() and decrease() methods. I have done this
 *  but also omitted the push() method, as Prim's algorithm doesn't use it. */
final class PrimHeap {
    static final class KeyValuePair {
        KeyValuePair(final int key, final int value) {
            this.key = key;
            this.value = value;
        }

        final int key;
        int value;
    }

    /** Constructs a new heap with sequential keys in [first, last].
     *  Each key initially maps to the max value of an int (for "infinity"). */
    PrimHeap(int first, final int last) {
        if (first > last)
            throw new IllegalArgumentException("size must be nonnegative");

        final int len = last - first + 1;
        _table = new HashMap<>(len);
        _elems = new ArrayList<>(len);

        for (int i = 0; i != len; ++i) {
            _table.put(first, i);
            _elems.add(new KeyValuePair(first++, Integer.MAX_VALUE));
        }
    }

    boolean isEmpty() { return _elems.isEmpty(); }

    int size() { return _elems.size(); }

    boolean contains(final int key) { return _table.containsKey(key); }

    KeyValuePair pop() {
        final KeyValuePair ret = _elems.get(0);
        final int last = size() - 1;

        if (last == 0) {
            _table.clear();
            _elems.clear();
        } else {
            _table.remove(ret.key);
            _elems.set(0, _elems.remove(last));
            siftDown(0);
        }

        return ret;
    }

    void decrease(final int key, final int value) {
        final int child = _table.get(key);
        final KeyValuePair entry = _elems.get(child);

        if (value < entry.value) {
            entry.value = value;
            siftUp(child);
        }
    }

    private static final int NO_CHILD = -1;

    private void siftUp(int child) {
        while (child != 0) {
            final int parent = (child - 1) / 2;
            if (orderOK(parent, child)) break;

            swap(child, parent);
            child = parent;
        }

        record(child);
    }

    private void siftDown(int parent) {
        for (; ; ) {
            final int child = pickChild(parent);
            if (child == NO_CHILD || orderOK(parent, child)) break;

            swap(parent, child);
            parent = child;
        }

        record(parent);
    }

    private int pickChild(final int parent) {
        final int left = parent * 2 + 1;
        if (left >= size()) return NO_CHILD;

        final int right = left + 1;
        return right == size() || orderOK(left, right) ? left : right;
    }

    private void swap(final int src, final int dest) {
        final KeyValuePair tmp = _elems.get(dest);
        _elems.set(dest, _elems.get(src));
        _elems.set(src, tmp);

        record(src);
    }

    private void record(final int src) {
        _table.put(_elems.get(src).key, src);
    }

    private boolean orderOK(final int parent, final int child) {
        return _elems.get(parent).value <= _elems.get(child).value;
    }

    private final Map<Integer, Integer> _table; // key -> index
    private final List<KeyValuePair> _elems; // index -> (key, value)
}

final class Edge {
    Edge(final int vertex, final int weight) {
        if (weight < 0)
            throw new IllegalArgumentException("negative weights not allowed");

        this.vertex = vertex;
        this.weight = weight;
    }

    final int vertex, weight;
}

final class Solution {
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            final List<List<Edge>> adj = readGraph(sc);
            System.out.println(computeMstWeight(adj, sc.nextInt()));
        }
    }

    private static final int MIN_VERTEX = 1; // the lowest-numbered vertex used

    /** Reads a graph (as [order, size, weighted edge]s) from a Scanner object.
     * @param sc    The Scanner used to read input.
     * @return The graph as an adjacency list. */
    private static List<List<Edge>> readGraph(final Scanner sc) {
        // read the order (vertex count) and "size" (edge count) for the graph
        int vertexCount = sc.nextInt(), edgeCount = sc.nextInt();
        if (vertexCount < 0)
            throw new IllegalStateException("negatively many vertices?");
        if (edgeCount < 0)
            throw new IllegalStateException("negatively many edges?");

        // create an empty adjacency list, one initially empty row per vertex
        final List<List<Edge>> adj = new ArrayList<>(MIN_VERTEX + vertexCount);
        for (int n = MIN_VERTEX; n != 0; --n) adj.add(Collections.emptyList());
        while (vertexCount-- != 0) adj.add(new ArrayList<>());

        // read the edges and use them to populate the adjacency list
        while (edgeCount-- != 0) {
             final int u = sc.nextInt(), v = sc.nextInt(), wt = sc.nextInt();
             adj.get(u).add(new Edge(v, wt));
             adj.get(v).add(new Edge(u, wt));
        }

        return adj;
    }

    /** Calculates a connected graph's MST's total weight via Prim's algorithm.
     * @param adj       An adjacency list for the graph whose MST is sought.
     * @param start     The vertex to start from in Prim's algorithm.
     * @return The sum of all edges's weights in the minimum spanning tree. */
    private static int computeMstWeight(final List<List<Edge>> adj,
                                        final int start) {
        int totalCost = 0;

        final PrimHeap costHeap = new PrimHeap(MIN_VERTEX, adj.size() - 1);
        costHeap.decrease(start, 0);

        while (!costHeap.isEmpty()) {
            final PrimHeap.KeyValuePair entry = costHeap.pop();
            totalCost += entry.value;

            for (final Edge edge : adj.get(entry.key)) {
                if (costHeap.contains(edge.vertex))
                    costHeap.decrease(edge.vertex, edge.weight);
            }
        }

        return totalCost;
    }

    private Solution() { throw new AssertionError(); }
}
