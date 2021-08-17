import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.OptionalInt;
import java.util.Scanner;
import java.util.SortedSet;
import java.util.StringJoiner;
import java.util.TreeSet;

/** An edge in a directed graph. */
final class Edge {
    Edge(final int src, final int dest) {
        this.src = src;
        this.dest = dest;
    }

    final int src;
    final int dest;
}

/** Walks through topological sorts in lexicographic order. */
final class KahnBacktracker {
    /**
     * Creates a backtracker for the specified graph.
     * @param order  The number of vertices in the graph.
     * @param edges  The edges in the graph.
     * @param chain  The initial topological sort.
     */
    KahnBacktracker(final int order, final List<Edge> edges,
                    final List<Integer> chain) {
        if (order < 0) {
            throw new IllegalArgumentException(
                    "graph can't have negatively many vertices");
        }

        if (order == 0) {
            throw new IllegalArgumentException(
                    "implementation doesn't accommodate empty graph");
        }

        _adj = new ArrayList<>(order + 1);
        while (_adj.size() <= order) _adj.add(new ArrayList<>());
        for (final Edge edge : edges) _adj.get(edge.src).add(edge.dest);

        _indegs = new int[order + 1];

        _chain = new ArrayList<>(chain);
        if (_chain.size() != order) {
            throw new IllegalArgumentException(
                    "initial chain has wrong length to be a topological sort");
        }
    }

    /**
     * Advances to the next topological sequence.
     * @return The next topological sequence, if any.
     */
    Optional<List<Integer>> next() {
        // Shorten the chain only as much as necessary.
        final OptionalInt src = retreat();

        if (src.isEmpty()) {
            assert _chain.isEmpty();
            return Optional.empty();
        }

        // Push the next bigger vertex at the tip of the chain.
        pushRootToChain(src.getAsInt());

        // Build the rest of the chain, smallest vertices first.
        advance();
        return Optional.of(new ArrayList<>(_chain));
    }

    /**
     * Attempts to shorten the chain just enough to replace its tip with a
     * lexicographically higher vertex.
     * @return The vertex that can be inserted at the tip, if any.
     */
    private OptionalInt retreat() {
        while (!_chain.isEmpty()) {
            final int src = popRootFromChain();
            _roots.add(src);
            final SortedSet<Integer> tail = _roots.tailSet(src + 1);

            if (!tail.isEmpty()) {
                // Put the new src in roots and return the old src.
                final int res = tail.first();
                tail.remove(res);
                return OptionalInt.of(res);
            }
        }

        return OptionalInt.empty();
    }

    /** Lengthens the chain to produce a completed topological sort. */
    private void advance() {
        while (!_roots.isEmpty()) {
            final Integer src = _roots.first();
            _roots.remove(src);
            pushRootToChain(src);
        }
    }

    /**
     * Pops a vertex from the chain for subsequent insertion as a root, and
     * increments its forward neighbors' indegrees.
     * @return  The popped vertex, which was previously the tip of the chain.
     */
    private int popRootFromChain() {
        final int src = _chain.remove(_chain.size() - 1);

        for (final int dest : _adj.get(src))
            if (_indegs[dest]++ == 0) _roots.remove(dest);

        return src;
    }

    /**
     * Pushes a presumably just-extracted root to the chain.
     * Decrements its forward neighbors' indegrees.
     * @param src  The extracted root, which will be the new tip of the chain.
     */
    private void pushRootToChain(final int src) {
        for (final int dest : _adj.get(src))
            if (--_indegs[dest] == 0) _roots.add(dest);

        _chain.add(src);
    }

    private final SortedSet<Integer> _roots = new TreeSet<>();
    private final List<List<Integer>> _adj;
    private final int[] _indegs;
    private final List<Integer> _chain;
}

final class Solution {
    /**
     * Reads a graph and presumed-correct topological sorting of it. Emits the
     * lexicographically next topological sorting of the graph, or -1 if none.
     * @param args  This program does not use command-line arguments.
     */
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            final int order = sc.nextInt(), edgeCount = sc.nextInt();
            final List<Edge> edges = readEdges(sc, edgeCount);
            final List<Integer> chain = readChain(sc, order);

            new KahnBacktracker(order, edges, chain).next().ifPresentOrElse(
                    Solution::printChain, () -> System.out.println("-1"));
        }
    }

    /**
     * Given the number of edges in the graph, read the edges.
     * @param sc  The scanner to read from.
     * @param edgeCount  The number of edges in the graph.
     * @return A list of the edges.
     */
    private static List<Edge>
    readEdges(final Scanner sc, final int edgeCount) {
        if (edgeCount < 0) {
            throw new IllegalArgumentException(
                    "can't read negatively many edges");
        }

        final List<Edge> edges = new ArrayList<>(edgeCount);

        while (edges.size() < edgeCount) {
            final int src = sc.nextInt(), dest = sc.nextInt();
            edges.add(new Edge(src, dest));
        }

        return edges;
    }

    /**
     * Given the order (vertex count) of the graph, reads the initial toposort.
     * @param sc  The scanner to read from.
     * @param order  The number of edges in the graph.
     * @return A list of the vertices in the initial topological sort.
     */
    private static List<Integer> readChain(final Scanner sc, final int order) {
        final List<Integer> chain = new ArrayList<>(order);
        while (chain.size() < order) chain.add(sc.nextInt());
        return chain;
    }

    /**
     * Prints a toposort.
     * @param chain  The sequence of vertices to print.
     */
    private static void printChain(final List<Integer> chain) {
        final StringJoiner sj = new StringJoiner(" ");
        chain.forEach(vertex -> sj.add(vertex.toString()));
        System.out.println(sj.toString());
    }

    /** The Solution class should not be instantiated. */
    private Solution() {
        throw new AssertionError();
    }
}
