import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.SortedSet;
import java.util.StringJoiner;
import java.util.TreeSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

final class Solution {
    public static void main(final String[] args) throws IOException {
        try (final FastScanner sc = new FastScanner()) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final List<List<OutEdge>> adj = readGraph(sc);
                final int start = sc.nextInt();
                printCosts(dijkstra(adj, start), start);
            }
        }
    }

    private static final int INFINITY = Integer.MAX_VALUE;

    private static final String NO_PATH = "-1";

    private static List<List<OutEdge>> readGraph(final FastScanner sc)
            throws IOException {
        final int vertexCount = sc.nextInt() + 1; // +1 for 1-based indexing
        final List<List<OutEdge>> adj = new ArrayList<>(vertexCount);
        while (adj.size() != vertexCount) adj.add(new ArrayList<>());

        for (int edgeCount = sc.nextInt(); edgeCount > 0; --edgeCount) {
            final int u = sc.nextInt();
            final int v = sc.nextInt();
            final int weight = sc.nextInt();

            adj.get(u).add(new OutEdge(v, weight));
            adj.get(v).add(new OutEdge(u, weight));
        }

        return adj;
    }

    private static int[] dijkstra(final List<List<OutEdge>> adj,
                                  final int start) {
        final int[] costs = new int[adj.size()];
        Arrays.fill(costs, INFINITY);
        costs[start] = 0;

        final SortedSet<Entry> entries = new TreeSet<>();
        entries.add(new Entry(start, 0));

        while (!entries.isEmpty()) {
            final Entry ent = entries.first();
            entries.remove(ent);
            if (ent.cost != costs[ent.vertex])
                throw new AssertionError("incorrect cost on removal");

            for (final OutEdge edge : adj.get(ent.vertex)) {
                final int newCost = costs[ent.vertex] + edge.weight;
                if (costs[edge.dest] <= newCost) continue;

                entries.remove(new Entry(edge.dest, costs[edge.dest]));
                entries.add(new Entry(edge.dest, newCost));
                costs[edge.dest] = newCost;
            }
        }

        return costs;
    }

    private static void printCosts(final int[] costs, final int start) {
        final StringJoiner sj = new StringJoiner(" ");

        for (int i = 1; i < costs.length; ++i) {
            if (i != start) {
                sj.add(costs[i] == INFINITY ? NO_PATH
                                            : Integer.toString(costs[i]));
            }
        }

        System.out.println(sj.toString());
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

final class OutEdge {
    OutEdge(final int dest, final int weight) {
        this.dest = dest;
        this.weight = weight;
    }

    final int dest;

    final int weight;
}

final class Entry implements Comparable<Entry> {
    Entry(final int vertex, final int cost) {
        this.vertex = vertex;
        this.cost = cost;
    }

    @Override
    public int compareTo(final Entry other) {
        final int by_cost = Integer.compare(cost, other.cost);
        return by_cost != 0 ? by_cost : Integer.compare(vertex, other.vertex);
    }

    @Override
    public boolean equals(final Object other) {
        throw new AssertionError(
                "Entry objects should not be compared with equals");
    }

    final int vertex;

    final int cost;
}
