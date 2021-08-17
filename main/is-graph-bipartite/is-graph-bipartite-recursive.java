class Solution {
    public boolean isBipartite(final int[][] graph) {
        final int[] vis = new int[graph.length];

        final IntPredicate isBipartiteFrom = new IntPredicate() {
            @Override
            public boolean test(final int src) {
                if (vis[src] == 0)
                    throw new AssertionError("vertex not colored");

                for (final int dest : graph[src]) {
                    if (vis[dest] == -vis[src]) continue;
                    if (vis[dest] != 0) return false;
                    vis[dest] = -vis[src];
                    if (!test(dest)) return false;
                }

                return true;
            }
        };

        for (int start = 0; start != graph.length; ++start) {
            if (vis[start] != 0) continue;

            vis[start] = 1;
            if (!isBipartiteFrom.test(start)) return false;
        }

        return true;
    }
}
