import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Deque;
import java.util.Iterator;
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

        for (int start = 0; start != adj.size(); ++start)
            topologicalSortHelper(out, vis, start);

        Collections.reverse(out);
        return out;
    }

    private void topologicalSortHelper(final List<Integer> out,
                                       final Color[] vis, final int start) {
        if (wasAlreadyExplored(vis, start)) return;
        vis[start] = Color.GRAY;
        final Deque<Frame> stack = new ArrayDeque<>();
        stack.push(new Frame(adj, start));

        while (!stack.isEmpty()) {
            final Frame frame = stack.element();

            if (!frame.iter.hasNext()) {
                vis[frame.vertex] = Color.BLACK;
                out.add(frame.vertex);
                stack.pop();
                continue;
            }

            final int dest = frame.iter.next();

            switch (vis[dest]) {
                case WHITE:
                    vis[dest] = Color.GRAY;
                    stack.push(new Frame(adj, dest));
                    continue;

                case GRAY:
                    throw new IllegalStateException(
                            "can't topologically sort a cyclic graph");

                case BLACK:
                    continue;
            }

            throw new AssertionError("invalid visitation state");
        }
    }

    private static boolean wasAlreadyExplored(final Color[] vis,
                                              final int start) {
        switch (vis[start]) {
            case WHITE:
                return false;

            case GRAY:
                throw new AssertionError(
                        "start vertex shouldn't be partially explored");

            case BLACK:
                return true;
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

/** Simulated stack frames for nonrecursively implemented graph traversal. */
final class Frame {
    Frame(final List<List<Integer>> adj, final int src) {
        iter = adj.get(src).iterator();
        vertex = src;
    }

    final Iterator<Integer> iter;
    final int vertex;
}
