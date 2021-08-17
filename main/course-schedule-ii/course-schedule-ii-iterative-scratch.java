import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Deque;
import java.util.Iterator;
import java.util.List;

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

        for (int start = 0; start != adj.size(); ++start) {
            if (hasCycleFrom(adj, vis, out, start)) {
                out.clear();
                break;
            }
        }

        return out;
    }

    private static boolean
    hasCycleFrom(final List<List<Integer>> adj, final Color[] vis,
                 final List<Integer> out, final int start) {
        final Deque<Frame> stack = startTraversal(adj, vis, start);
        if (stack == null) return false;

        while (!stack.isEmpty()) {
            final Frame frame = stack.element();

            if (!frame.pos.hasNext()) {
                vis[frame.vertex] = Color.BLACK;
                out.add(frame.vertex);
                stack.pop();
                continue;
            }

            final int neighbor = frame.pos.next();

            switch (vis[neighbor]) {
            case WHITE:
                vis[neighbor] = Color.GRAY;
                stack.push(new Frame(adj, neighbor));
                continue;

            case GRAY:
                return true;

            case BLACK:
                continue;
            }

            throw new AssertionError("invalid visitation state");
        }

        return false;
    }

    private static Deque<Frame>
    startTraversal(final List<List<Integer>> adj, final Color[] vis,
                   final int start) {
        switch (vis[start]) {
        case WHITE:
            vis[start] = Color.GRAY;
            final Deque<Frame> stack = new ArrayDeque<>();
            stack.push(new Frame(adj, start));
            return stack;

        case GRAY:
            throw new IllegalStateException("cycle already found");

        case BLACK:
            return null;
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

/** "Stack frames" for iteratively implemented recursive graph traversal. */
final class Frame {
    Frame(final List<List<Integer>> adj, final int vertex) {
        this.vertex = vertex;
        this.pos = adj.get(vertex).iterator();
    }

    final int vertex;

    final Iterator<Integer> pos;
}

final class UnitTest {
    public static void main(final String[] args) {
        final int[][] a = { {1, 0} };
        test(2, a);

        final int[][] b = { {1, 0}, {2, 0}, {3, 1}, {3, 2} };
        test(4, b);

        final int[][] c = { {2, 1}, {1, 0}, {2, 0}, {3, 1}, {3, 2} };
        test(4, c);

        final int[][] d = { {1, 2}, {1, 0}, {2, 0}, {3, 1}, {3, 2} };
        test(4, d);

        final int[][] e = { { 0, 1 }, { 1, 0 } };
        test(2, e);

        final int[][] f = { };
        test(7, f);

        final int[][] g = { {2, 4}, {1, 5} };
        test(7, g);
    }

    private static void
    test(final int numCourses, final int[][] prerequisites) {
        final int[] order = new Solution().findOrder(numCourses, prerequisites);
        System.out.println(Arrays.toString(order));
    }
}
