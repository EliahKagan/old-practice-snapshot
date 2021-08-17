import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.SortedSet;
import java.util.TreeSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

final class Solution {
    public static void main(final String[] args) throws IOException {
        try (final FastScanner sc = new FastScanner()) {
            final List<List<Edge>> adj = readGraph(sc);
            System.out.println(prim(adj, sc.nextInt()));
        }
    }

    private static List<List<Edge>> readGraph(final FastScanner sc)
            throws IOException {
        final int vertexCount = sc.nextInt() + 1; // +1 for 1-based indexing
        final List<List<Edge>> adj = new ArrayList<>(vertexCount);
        while (adj.size() != vertexCount) adj.add(new ArrayList<>());

        for (int edgeCount = sc.nextInt(); edgeCount > 0; --edgeCount) {
            final int u = sc.nextInt();
            final int v = sc.nextInt();
            final int weight = sc.nextInt();

            adj.get(u).add(new Edge(v, weight));
            adj.get(v).add(new Edge(u, weight));
        }

        return adj;
    }

    private static final Edge NO_EDGE = new Edge(0, Integer.MAX_VALUE);

    private static final Edge SELF_EDGE = new Edge(0, 0);

    private static int prim(final List<List<Edge>> adj, final int start) {
        int totalCost = 0;

        final Edge[] map = new Edge[adj.size()];
        Arrays.fill(map, NO_EDGE);
        map[start] = SELF_EDGE;

        final SortedSet<Edge> heap = new TreeSet<>();
        heap.add(new Edge(start, 0));

        while (!heap.isEmpty()) {
            final Edge in = heap.first();
            heap.remove(in);

            if (in.weight != map[in.neighbor].weight)
                throw new AssertionError("incorrect weight on removal");

            map[in.neighbor] = SELF_EDGE;
            totalCost += in.weight;

            for (final Edge out : adj.get(in.neighbor)) {
                if (map[out.neighbor].compareTo(out) <= 0) continue;

                heap.remove(map[out.neighbor]);
                heap.add(out);
                map[out.neighbor] = out;
            }
        }

        return totalCost;
    }

    private Solution() {
        throw new AssertionError(
                "the Solution class should not be instantiated");
    }
}

final class FastScanner implements AutoCloseable {
    @Override
    public void close() throws IOException {
        _reader.close();
    }

    int nextInt() throws IOException {
        if (!_matcher.find()) {
            _matcher.reset(_reader.readLine());
            if (!_matcher.find()) throw new NoSuchElementException();
        }

        return Integer.parseInt(_matcher.group());
    }

    private final BufferedReader _reader =
            new BufferedReader(new InputStreamReader(System.in));

    private final Matcher _matcher = Pattern.compile("\\S+").matcher("");
}

final class Edge implements Comparable<Edge> {
    Edge(final int neighbor, final int weight) {
        this.neighbor = neighbor;
        this.weight = weight;
    }

    @Override
    public int compareTo(final Edge other) {
        final int byWeight = Integer.compare(weight, other.weight);

        return byWeight != 0 ? byWeight
                             : Integer.compare(neighbor, other.neighbor);
    }

    @Override
    public boolean equals(final Object other) {
        throw new AssertionError(
                "Edge objects should not be compared with .equals()");
    }

    final int neighbor;

    final int weight;
}
