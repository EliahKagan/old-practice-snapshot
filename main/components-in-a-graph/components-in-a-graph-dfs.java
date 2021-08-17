import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;
import java.util.Scanner;

final class Solution {
    private static List<List<Integer>>
    readGraph(final Scanner sc, final int vertexCount, int edgeCount) {
        // Make an empty adjacency list.
        final List<List<Integer>> adj = new ArrayList<>(vertexCount);
        while (adj.size() < vertexCount) adj.add(new ArrayList<>());

        // Populate the adjacency list.
        while (edgeCount-- > 0) {
            final int u = sc.nextInt(), v = sc.nextInt();
            adj.get(u).add(v);
            adj.get(v).add(u);
        }

        return adj;
    }

    private static int measure(final List<List<Integer>> adj,
                               final boolean[] vis, final int start) {
        if (vis[start]) return 0;
        vis[start] = true;

        final Deque<Integer> stack = new ArrayDeque<>();
        stack.push(start);

        int count = 1;

        while (!stack.isEmpty()) {
            final int src = stack.pop();

            for (final int dest : adj.get(src)) {
                if (vis[dest]) continue;
                vis[dest] = true;
                stack.push(dest);
                ++count;
            }
        }

        return count;
    }

    private static void
    printMinMaxNontrivialComponentSizes(final List<List<Integer>> adj) {
        int min = Integer.MAX_VALUE, max = Integer.MIN_VALUE;

        final boolean[] vis = new boolean[adj.size()];

        for (int start = 1; start < vis.length; ++start) {
            final int count = measure(adj, vis, start);

            if (count > 1) {
                min = Math.min(min, count);
                max = Math.max(max, count);
            }
        }

        System.out.format("%d %d%n", min, max);
    }

    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            final int n = sc.nextInt();
            final List<List<Integer>> adj = readGraph(sc, n * 2 + 1, n);
            printMinMaxNontrivialComponentSizes(adj);
        }
    }

    private Solution() { throw new AssertionError(); }
}
