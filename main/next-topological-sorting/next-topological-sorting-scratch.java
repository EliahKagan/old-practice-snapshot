import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.OptionalInt;
import java.util.Scanner;
import java.util.SortedSet;
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
        // FIXME: implement this
    }

    /**
     * Attempts to shorten the chain just enough to replace its tip with a
     * lexicographically higher vertex.
     * @return The vertex that can be inserted at the tip, if any.
     */
    private OptionalInt retreat() {
        while (!_chain.isEmpty()) {
            final int src = popRootFromChain();
            final SortedSet<Integer> tail = _roots.tailSet(src + 1);

            if (!tail.isEmpty()) {
                // Put the new src in roots and return the old src.
                final int res = tail.first();
                tail.remove(res);
                _roots.add(src);
                return OptionalInt.of(res);
            }

            _roots.add(src);
        }

        return OptionalInt.empty();
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
