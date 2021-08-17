class Solution {
    public int[] findOrder(final int numCourses, final int[][] prerequisites) {
        return buildPrerequisitesGraph(numCourses, prerequisites)
                .topologicalSort();
    }

    private static Graph buildPrerequisitesGraph(final int numCourses,
                                                 final int[][] prerequisites) {
        final Graph graph = new Graph(numCourses);
        for (final int[] edge : prerequisites) graph.addEdge(edge[1], edge[0]);
        return graph;
    }
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

    int[] topologicalSort() {
        checkAndUnsetTopologicalSortPrecondition();
        final int[] out = new int[adj.size()];
        int outpos = 0;

        for (final Queue<Integer> roots = getRoots(); !roots.isEmpty(); ) {
            final int src = roots.remove();

            for (final int dest : adj.get(src))
                if (--inorders[dest] == 0) roots.add(dest);

            out[outpos++] = src;
        }

        checkTopologicalSortOutputSize(outpos);
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

    private void checkTopologicalSortOutputSize(final int outpos) {
        if (outpos != adj.size()) {
            throw new IllegalStateException(
                    "can't topologically sort a cyclic graph");
        }
    }

    final List<List<Integer>> adj;
    final int[] inorders;
    boolean ranTopologicalSort = false;
}
