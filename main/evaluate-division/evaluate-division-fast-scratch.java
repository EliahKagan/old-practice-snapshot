import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Queue;

final class Edge {
    Edge(final int dest, final double weight) {
        this.dest = dest;
        this.weight = weight;
    }

    final int dest;

    final double weight;
}

final class RatioGraph {
    static final double NOT_KNOWN = -1.0; // must be negative

    RatioGraph(final List<List<Edge>> adj) {
        _vis = new int[adj.size()];
        _potentials = new double[adj.size()];
        computePotentials(adj);
    }

    double query(final int numeratorVertex, final int denominatorVertex) {
        return _vis[numeratorVertex] == _vis[denominatorVertex]
                ? _potentials[numeratorVertex] / _potentials[denominatorVertex]
                : NOT_KNOWN;
    }

    private void computePotentials(final List<List<Edge>> adj) {
        final Queue<Integer> queue = new ArrayDeque<>();
        int component = 0;

        for (int vertex = 0; vertex != adj.size(); ++vertex) {
            if (_vis[vertex] != 0) continue;

            _vis[vertex] = ++component;
            _potentials[vertex] = 1.0;
            queue.add(vertex);
            bfs(adj, queue, component);
        }
    }

    private void bfs(final List<List<Edge>> adj, final Queue<Integer> queue,
                     final int component) {
        while (!queue.isEmpty()) {
            final int src = queue.remove();

            for (final Edge edge : adj.get(src)) {
                if (_vis[edge.dest] != 0) continue;

                _vis[edge.dest] = component;
                _potentials[edge.dest] = _potentials[src] * edge.weight;
                queue.add(edge.dest);
            }
        }
    }

    private final int[] _vis;

    private final double[] _potentials;
}

class Solution {
    public double[]
    calcEquation(final String[][] equations, final double[] values,
                 final String[][] queries) {
        final Map<String, Integer> vertices = mapVariablesToVertices(equations);

        final RatioGraph graph =
                new RatioGraph(buildAdjacencyList(vertices, equations, values));

        return processQueries(graph, vertices, queries);
    }

    private static Map<String, Integer>
    mapVariablesToVertices(final String[][] equations) {
        final Map<String, Integer> vertices = new HashMap<>();

        for (final String[] pair : equations) {
            checkPair("expressions", pair);

            for (final String variable : pair)
                vertices.computeIfAbsent(variable, k -> vertices.size());
        }

        return vertices;
    }

    private static List<List<Edge>>
    buildAdjacencyList(final Map<String, Integer> vertices,
                       final String[][] equations, final double[] values) {
        checkInputLengths(equations, values);
        final List<List<Edge>> adj = createEmptyAdjacencyList(vertices.size());

        for (int pos = 0; pos != equations.length; ++pos) {
            final int numeratorVertex = vertices.get(equations[pos][0]);
            final int denominatorVertex = vertices.get(equations[pos][1]);
            final double ratio = values[pos];
            checkRatio(ratio);

            adj.get(denominatorVertex)
               .add(new Edge(numeratorVertex, ratio));

            adj.get(numeratorVertex)
               .add(new Edge(denominatorVertex, 1.0 / ratio));
        }

        return adj;
    }

    private static List<List<Edge>> createEmptyAdjacencyList(int size) {
        final List<List<Edge>> adj = new ArrayList<>(size);
        while (size-- != 0) adj.add(new ArrayList<>());
        return adj;
    }

    private static void
    checkInputLengths(final String[][] equations, final double[] values) {
        if (equations.length != values.length) {
            throw new IllegalArgumentException(
                    "equations and values must be of the same size");
        }
    }

    private static void checkRatio(final double ratio) {
        if (ratio <= 0.0) {
            throw new IllegalArgumentException(
                    "quotient values must be (strictly) positive");
        }
    }

    private static double[]
    processQueries(final RatioGraph graph, final Map<String, Integer> vertices,
                   final String[][] queries) {
        final double[] results = new double[queries.length];

        for (int pos = 0; pos != queries.length; ++pos)
            results[pos] = retrieveRatio(graph, vertices, queries[pos]);

        return results;
    }

    private static double
    retrieveRatio(final RatioGraph graph, final Map<String, Integer> vertices,
                  final String[] query) {
        checkPair("queries", query);

        final Integer numeratorVertex = vertices.get(query[0]);
        if (numeratorVertex == null) return RatioGraph.NOT_KNOWN;

        final Integer denominatorVertex = vertices.get(query[1]);
        if (denominatorVertex == null) return RatioGraph.NOT_KNOWN;

        return graph.query(numeratorVertex, denominatorVertex);
    }

    private static void
    checkPair(final String description, final String[] pair) {
        if (pair.length != 2) {
            throw new IllegalArgumentException(
                    "quotient " + description
                                + " must have exactly two operands");
        }
    }
}

final class UnitTest {
    public static void main(final String[] args) {
        test(new String[][] { {"a", "b"}, {"b", "c"} },
                new double[] { 2.0, 3.0 },
                new String[][] { {"a", "c"}, {"b", "a"}, {"a", "e"},
                        {"a", "a"}, {"x", "x"} });

        test(new String[][] { {"a", "b"}, {"b", "c"}, {"c", "d"}, {"d", "e"},
                        {"e", "f"}, {"c", "g"}, {"g", "h"}, {"h", "i"} },
                new double[] { 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8 },
                new String[][] { {"a", "e"}, {"a", "i"}, {"e", "i"} });

        test(new String[][] { {"a", "s"}, {"b", "t"}, {"c", "u"}, {"d", "v"},
                        {"e", "w"},
                        {"a", "c"}, {"c", "e"}, {"e", "d"}, {"d", "b"} },
                new double[] { 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 3.0, 5.0, 7.0 },
                new String[][] { {"a", "b"} });
    }

    private static void
    test(final String[][] equations, final double[] values,
         final String[][] queries) {
        for (final double result
                : new Solution().calcEquation(equations, values, queries))
            System.out.println(result);

        System.out.println();
    }

    private UnitTest() { throw new AssertionError(); }
}
