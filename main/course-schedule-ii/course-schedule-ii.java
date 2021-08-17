class Solution {
    public int[] findOrder(final int numCourses, final int[][] prerequisites) {
        final List<List<Integer>> adj = buildAdjacencyList(numCourses,
                                                           prerequisites);

        return reverseTopologicalSort(adj).stream().mapToInt(x -> x).toArray();
    }

    private static List<List<Integer>>
    buildAdjacencyList(int vertexCount, final int[][] edges) {
        // create an empty adjacency list with the correct number of rows
        final List<List<Integer>> adj = new ArrayList<>(vertexCount);
        while (vertexCount-- != 0) adj.add(new ArrayList<>());

        // populate the adjacency list with information about all the edges
        for (final int[] edge : edges) adj.get(edge[0]).add(edge[1]);
        return adj;
    }

    private static List<Integer>
    reverseTopologicalSort(final List<List<Integer>> adj) {
        final Color[] vis = new Color[adj.size()];
        Arrays.fill(vis, Color.WHITE);

        final List<Integer> out = new ArrayList<>(adj.size());

        for (int src = 0; src != adj.size(); ++src) {
            if (hasCycleFrom(adj, vis, out, src)) {
                out.clear();
                break;
            }
        }

        return out;
    }

    private static boolean
    hasCycleFrom(final List<List<Integer>> adj, final Color[] vis,
                 final List<Integer> out, final int src) {
        switch (vis[src]) {
        case WHITE:
            vis[src] = Color.GRAY;

            for (final int dest : adj.get(src))
                if (hasCycleFrom(adj, vis, out, dest)) return true;

            vis[src] = Color.BLACK;
            out.add(src);
            return false;

        case GRAY:
            return true;

        case BLACK:
            return false;
        }

        throw new AssertionError("invalid visitation state");
    }
}

/** Visitation states for traversing a directed graph. */
enum Color {
    /** Unvisited */
    WHITE,

    /** Visited but not yet fully explored */
    GRAY,

    /** Visited and fully explored */
    BLACK
}
