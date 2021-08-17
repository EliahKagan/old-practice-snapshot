import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
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
        adj = new ArrayList<>();
        while (adj.size() < vertexCount) adj.add(new ArrayList<Integer>());
    }

    void addEdge(final int src, final int dest) {
        adj.get(src).add(dest);
    }

    List<Integer> topologicalSort() {
        final List<Integer> out = new ArrayList<>(adj.size());

        final Color[] vis = new Color[adj.size()];
        Arrays.fill(vis, Color.WHITE);

        for (int src = 0; src != adj.size(); ++src)
            topologicalSortHelper(out, vis, src);

        Collections.reverse(out);
        return out;
    }

    private void topologicalSortHelper(final List<Integer> out,
                                       final Color[] vis, final int src) {
        switch (vis[src]) {
            case WHITE:
                vis[src] = Color.GRAY;

                for (final int dest : adj.get(src))
                    topologicalSortHelper(out, vis, dest);

                vis[src] = Color.BLACK;

                out.add(src);
                return;

            case GRAY:
                throw new IllegalStateException(
                        "can't topologically sort a cyclic graph");

            case BLACK:
                return;
        }

        throw new AssertionError("invalid visitation state");
    }

    private final List<List<Integer>> adj;
}

/** Vistation states for traversing a directed graph. */
enum Color {
    WHITE,  // unvisited
    GRAY,   // visited but not fully explored
    BLACK   // fully explored
}
