import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.Scanner;

final class Solution {
    public static void main(final String[] args) {
        print(readGraph().topologicalSort());
    }

    private static Graph readGraph() {
        try (final Scanner sc = new Scanner(System.in)) {
            final Graph graph = new Graph(sc.nextInt());

            for (int e = sc.nextInt(); e > 0; --e) {
                final int src = sc.nextInt(), dest = sc.nextInt();
                graph.addEdge(src, dest);
            }

            return graph;
        }
    }

    private static <T> void print(final List<T> values) {
        String sep = "";
        for (final T x : values) {
            System.out.format("%s%s", sep, x);
            sep = " ";
        }

        System.out.println();
    }

    private Solution() { throw new AssertionError(); }
}

/** A directed graph. */
final class Graph {
    Graph(final int vertexCount) {
        adj = new ArrayList<>(vertexCount);
        while (adj.size() != vertexCount) adj.add(new ArrayList<Integer>());

        inorders = new int[vertexCount];
    }

    void addEdge(final int src, final int dest) {
        adj.get(src).add(dest);
        ++inorders[dest];
    }

    List<Integer> topologicalSort() {
        checkAndUnsetTopologicalSortPrecondition();
        final List<Integer> out = new ArrayList<>(adj.size());

        for (final Queue<Integer> roots = getRoots(); !roots.isEmpty(); ) {
            final int src = roots.remove();

            for (final int dest : adj.get(src))
                if (--inorders[dest] == 0) roots.add(dest);

            out.add(src);
        }

        checkTopologicalSortOutputSize(out);
        return out;
    }

    private Queue<Integer> getRoots() {
        final Queue<Integer> roots = new ArrayDeque<>();

        for (int src = 0; src != adj.size(); ++src)
            if (inorders[src] == 0) roots.add(src);

        return roots;
    }

    private void checkAndUnsetTopologicalSortPrecondition() {
        if (ranTopologicalSort)
            throw new IllegalStateException("already ran topological sort");

        ranTopologicalSort = true;
    }

    private void checkTopologicalSortOutputSize(final List<Integer> out) {
        if (out.size() == adj.size()) return;

        if (out.size() > adj.size()) {
            throw new AssertionError(
                    "topological sort has more vertices than the graph!");
        }

        throw new IllegalStateException(
                    "can't topologically sort a cyclic graph");
    }

    final List<List<Integer>> adj;
    final int[] inorders;
    boolean ranTopologicalSort = false;
}
