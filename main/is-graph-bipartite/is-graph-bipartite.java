class Solution {
    public boolean isBipartite(final int[][] graph) {
        final int[] vis = new int[graph.length];

        for (int start = 0; start != graph.length; ++start)
            if (!isBipartiteFrom(graph, vis, start)) return false;

        return true;
    }

    private static boolean
    isBipartiteFrom(final int[][] graph, final int[] vis, final int start) {
        if (vis[start] != 0) return true;
        vis[start] = 1;

        final Deque<Integer> stack = new ArrayDeque<>();
        stack.push(start);

        while (!stack.isEmpty()) {
            final int src = stack.pop();
            for (final int dest : graph[src]) {
                if (vis[dest] == -vis[src]) continue;
                if (vis[dest] != 0) return false;
                vis[dest] = -vis[src];
                stack.push(dest);
            }
        }

        return true;
    }
}
