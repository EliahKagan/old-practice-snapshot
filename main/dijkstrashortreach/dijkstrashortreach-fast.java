import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringJoiner;
import java.util.StringTokenizer;

/** A modified binary minheap, suitable for Prim's or Dijkstra's algorithms.
 *  Traditionally one adds contains() and decrease() methods. I have done this
 *  but also omitted the push() method, as those algorithms don't need it. */
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

/** A pair of vertices representing an undirected edge of unspecified weight.
 *  This type is effectively an implementation detail for the Solution class. */
final class Endpoints {
    Endpoints(final int u, final int v) {
        if (u > v) {
            this.u = v;
            this.v = u;
        } else {
            this.u = u;
            this.v = v;
        }
    }

    boolean equals(final Endpoints other) {
        return u == other.u && v == other.v;
    }

    @Override
    public boolean equals(final Object other) {
        // Endpoints is effectively an implementation detail. Comparing an
        // object of this type to an object of another type or to null would
        // always be a bug, and it is better for it to throw than return false.
        return equals((Endpoints)other);
    }

    @Override
    public int hashCode() {
        return (17 * 31 + u) * 31 + v;
    }

    final int u, v;
}

/** An element of a row of an adjacency list of a weighted undirected graph. */
final class Neighbor {
    Neighbor(final int dest, final int wt) {
        if (wt < 0)
            throw new IllegalArgumentException("negative weights not allowed");

        this.dest = dest;
        this.wt = wt;
    }

    final int dest, wt;
}

final class Solution {
    public static void main(final String[] args) throws IOException {
        try (final InputStreamReader isr = new InputStreamReader(System.in);
             final BufferedReader br = new BufferedReader(isr)) {
            for (int t = getVal(br); t > 0; --t) {
                final List<List<Neighbor>> adj = readGraph(br);
                final int start = getVal(br);

                final int[] costs = computeShortestReaches(adj, start, -1);

                final StringJoiner sj = new StringJoiner(" ");
                for (int i = MIN_VERTEX; i != costs.length; ++i)
                    if (i != start) sj.add(Integer.toString(costs[i]));

                System.out.println(sj);
            }
        }
    }

    private static final int MIN_VERTEX = 1; // the lowest-numbered vertex used

    /** Reads a graph as [order, size], [u1, v1, wt1], [u2, v2, wt2], ...
     * @param br    The BufferedReader used to read input.
     * @return The graph as an adjacency list. */
    private static List<List<Neighbor>> readGraph(final BufferedReader br)
            throws IOException {
        final StringTokenizer st = new StringTokenizer(br.readLine());
        final int vertexCount = getVal(st), edgeCount = getVal(st);

        final List<List<Neighbor>> adj = getEmptyAdjacencyList(vertexCount);

        readSimpleGraphEdges(br, edgeCount).forEach((uv, weight) -> {
            final int u = uv.u, v = uv.v, wt = weight;
            adj.get(u).add(new Neighbor(v, wt));
            adj.get(v).add(new Neighbor(u, wt));
        });

        return adj;
    }

    /** Creates an empty adjacency list: one initially empty row per vertex.
     * @param vertexCount   The number of vertices, starting from MIN_VERTEX.
     * @return An adjacency list of MIN_VERTEX + vertexCount empty rows. */
    private static List<List<Neighbor>> getEmptyAdjacencyList(int vertexCount) {
        if (vertexCount < 0)
            throw new IllegalArgumentException("negatively many vertices?");

        final int size = MIN_VERTEX + vertexCount;

        final List<List<Neighbor>> adj = new ArrayList<>(size);
        for (int n = MIN_VERTEX; n != 0; --n) adj.add(Collections.emptyList());
        while (vertexCount-- != 0) adj.add(new ArrayList<>());

        assert adj.size() == size;
        return adj;
    }

    /** Reads a graph as a compact adjacency matrix consisting of a map from
     *  endpoint pairs represented by Endpoints objects to Integer weights.
     * @param br        The BufferedReader used to read input.
     * @param edgeCount The "size" of the graph -- the number of edge to read.
     * @return  A map, edges, where edges.get(new Endpoints(u, v)) is the weight
     *          associated with the undirected edge (u, v). */
    private static Map<Endpoints, Integer> readSimpleGraphEdges(
            final BufferedReader br, int edgeCount) throws IOException {
        if (edgeCount < 0)
            throw new IllegalArgumentException("negatively many edges?");

        final Map<Endpoints, Integer> edges = new HashMap<>();

        while (edgeCount-- != 0) {
            final StringTokenizer st = new StringTokenizer(br.readLine());
            final int u = getVal(st), v = getVal(st), wt = getVal(st);
            if (u != v) edges.merge(new Endpoints(u, v), wt, Math::min);
        }

        return edges;
    }

    private static int getVal(final BufferedReader br) throws IOException {
        return Integer.parseInt(br.readLine());
    }

    private static int getVal(final StringTokenizer st) {
        return Integer.parseInt(st.nextToken());
    }

    /** Calculates all the shortest reaches in a graph from a given start
     * vertex, using Dijkstra's algorithm.
     * @param adj               An adjacency list for the graph.
     * @param start             The vertex to measure shortest paths from.
     * @param unreachableCost   The "cost" to indicate an unreachable vertex.
     * @return A costs array, where costs[i] is the cost of the shortest path
     *         from the starting vertex to vertex i, or unreachableCost. */
    private static int[] computeShortestReaches(final List<List<Neighbor>> adj,
                                                final int start,
                                                final int unreachableCost)
    {
        final int[] costs = new int[adj.size()];
        Arrays.fill(costs, unreachableCost);
        costs[start] = 0;

        final PrimHeap costHeap = new PrimHeap(MIN_VERTEX, adj.size() - 1);
        costHeap.decrease(start, 0);

        while (!costHeap.isEmpty()) {
            final PrimHeap.KeyValuePair entry = costHeap.pop();

            final int wt = entry.value;
            if (wt == Integer.MAX_VALUE) break;

            final int src = entry.key;
            costs[src] = entry.value;

            for (final Neighbor neighbor : adj.get(src)) {
                final int dest = neighbor.dest;
                if (costHeap.contains(dest))
                    costHeap.decrease(dest, wt + neighbor.wt);
            }
        }

        return costs;
    }

    private Solution() { throw new AssertionError(); }
}
