import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public boolean
    canFinish(final int numCourses, final int[][] prerequisites) {
        if (numCourses < 0)
            throw new IllegalArgumentException("numCourses can't be negative");

        // All courses can be taken if there are no prerequisite cycles.
        return !hasCycle(buildAdjacencyList(numCourses, prerequisites));
    }

    private static List<List<Integer>>
    buildAdjacencyList(final int numCourses, final int[][] prerequisites) {
        // Create an empty adjacency list.
        final List<List<Integer>> adj = new ArrayList<>(numCourses);
        while (adj.size() != numCourses) adj.add(new ArrayList<>());

        // Populate the adjacency list.
        for (int i = 0; i != numCourses; ++i)
            adj.get(prerequisites[i][1]).add(prerequisites[i][0]);

        return adj;
    }

    private static boolean hasCycle(final List<List<Integer>> adj) {
        // Create an empty visitation list.
        final Color[] vis = new Color[adj.size()];
        Arrays.fill(vis, Color.WHITE);

        // Look for a cycle from every totally unvisited ("WHITE") vertex.
        for (int start = 0; start != vis.length; ++start)
            if (hasCycleFrom(adj, vis, start)) return true;

        return false;
    }

    private static boolean hasCycleFrom(final List<List<Integer>> adj,
                                        final Color[] vis, final int start) {
        switch (vis[start]) {
        case WHITE:
            vis[start] = Color.GRAY;

            for (final int neighbor : adj.get(start))
                if (hasCycleFrom(adj, vis, neighbor)) return true;

            vis[start] = Color.BLACK;

            return false;

        case GRAY:
            return true;

        case BLACK:
            return false;
        }

        throw new AssertionError("unreachable code");
    }

    private enum Color { WHITE, GRAY, BLACK };
}
