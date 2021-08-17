import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;

final class DisjointSets {
    DisjointSets(final int size) {
        _parents = new int[size];
        for (int i = 0; i != size; ++i) _parents[i] = i;

        _ranks = new int[size];
    }

    /** If i and j are in different sets, joins the sets.
     *  @return true if the sets were separate, false otherwise. */
    boolean union(int i, int j) {
        // find the ancestors and stop if they are already the same
        i = findSet(i);
        j = findSet(j);
        if (i == j) return false;

        // unite by rank
        if (_ranks[i] < _ranks[j]) {
            _parents[i] = j;
        } else {
            if (_ranks[i] == _ranks[j]) ++_ranks[i];
            _parents[j] = i;
        }

        return true;
    }

    private int findSet(int i) {
        // find the ancestor
        int j = i;
        while (j != _parents[j]) j = _parents[j];

        // compress the path
        while (i != j) {
            final int next = _parents[i];
            _parents[i] = j;
            i = next;
        }

        return j;
    }

    private final int[] _parents, _ranks;
}

final class Edge implements Comparable<Edge> {
    Edge(final int u, final int v, final int wt) {
        this.u = u;
        this.v = v;
        this.wt = wt;
    }

    @Override
    public int compareTo(final Edge other) {
        return Integer.compare(wt, other.wt);
    }

    final int u, v, wt;
}

final class Solution {
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            final int vertexCount = sc.nextInt(), edgeCount = sc.nextInt();

            final int weight = computeMstWeight(vertexCount,
                                                readEdges(sc, edgeCount));

            System.out.println(weight);
        }
    }

    private static List<Edge> readEdges(final Scanner sc, int edgeCount) {
        final List<Edge> edges = new ArrayList<>(edgeCount);

        while (edgeCount-- != 0) {
            final int u = sc.nextInt(), v = sc.nextInt(), wt = sc.nextInt();
            edges.add(new Edge(u, v, wt));
        }

        return edges;
    }

    private static int computeMstWeight(final int vertexCount,
                                        final List<Edge> edges) {
        if (vertexCount < 2) return 0;

        // Add 1 because we are not using vertex 0 (we want 1-based indexing).
        final DisjointSets sets = new DisjointSets(vertexCount + 1);

        // This may save time because we only pop edges until we have an MST.
        final Queue<Edge> heap = new PriorityQueue<>(edges);

        // Pick up edges until we have an MST or all edges were considered.
        int weight = 0;
        for (int needed = vertexCount - 1; needed != 0 && !heap.isEmpty(); ) {
            final Edge edge = heap.remove();

            if (sets.union(edge.u, edge.v)) {
                weight += edge.wt;
                --needed;
            }
        }

        return weight;
    }

    private Solution() { throw new AssertionError(); }
}
