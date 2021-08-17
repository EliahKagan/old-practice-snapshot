import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

class Solution {
    public double[]
    calcEquation(final String[][] equations, final double[] values,
                 final String[][] queries) {
        final Map<String, Integer> indices = mapVariablesToIndices(equations);

        final double[][] ratios = createUnpopulatedRatioMatrix(indices.size());
        populateRatioMatrix(ratios, indices, equations, values);
        completeRatioMatrix(ratios);

        return processQueries(ratios, indices, queries);
    }

    private static Map<String, Integer>
    mapVariablesToIndices(final String[][] equations) {
        final Map<String, Integer> indices = new HashMap<>();

        for (final String[] pair : equations) {
            if (pair.length != 2) {
                throw new IllegalArgumentException(
                        "quotient expressions must have exactly two operands");
            }

            for (final String variable : pair)
                indices.computeIfAbsent(variable, k -> indices.size());
        }

        return indices;
    }

    private static double[][] createUnpopulatedRatioMatrix(final int size) {
        final double[][] ratios = new double[size][size];
        for (final double[] row : ratios) Arrays.fill(row, NOT_KNOWN);
        for (int h = 0; h != size; ++h) ratios[h][h] = 1.0;
        return ratios;
    }

    private static void
    populateRatioMatrix(final double[][] ratios,
                        final Map<String, Integer> indices,
                        final String[][] equations, final double[] values) {
        if (equations.length != values.length) {
            throw new IllegalArgumentException(
                    "equations and values must have the same size");
        }

        for (int pos = 0; pos != equations.length; ++pos) {
            final int i = indices.get(equations[pos][0]);
            final int j = indices.get(equations[pos][1]);
            final double r = values[pos];

            if (r <= 0.0) {
                throw new IllegalArgumentException(
                        "quotient values must be (strictly) positive");
            }

            if (ratios[i][j] < 0.0) ratios[i][j] = r;
            if (ratios[j][i] < 0.0) ratios[j][i] = 1.0 / r;
        }
    }

    private static void completeRatioMatrix(final double[][] ratios) {
        for (int i = 0; i != ratios.length; ++i) {
            for (int j = 0; j != ratios.length; ++j)
                if (ratios[i][j] < 0.0) tryFixEntry(ratios, i, j);
        }
    }

    private static void
    tryFixEntry(final double[][] ratios, final int i, final int j) {
        for (int k = 0; k != ratios.length; ++k) {
            if (ratios[i][k] >= 0.0 && ratios[k][j] >= 0.0) {
                ratios[i][j] = ratios[i][k] * ratios[k][j];
                break;
            }
        }
    }

    private static double[]
    processQueries(final double[][] ratios, final Map<String, Integer> indices,
                   final String[][] queries) {
        final double[] results = new double[queries.length];

        for (int pos = 0; pos != queries.length; ++pos)
            results[pos] = retrieveRatio(ratios, indices, queries[pos]);

        return results;
    }

    private static double
    retrieveRatio(final double[][] ratios, final Map<String, Integer> indices,
                  final String[] query) {
        if (query.length != 2) {
            throw new IllegalArgumentException(
                    "quotient queries must have exactly two operands");
        }

        final Integer i = indices.get(query[0]), j = indices.get(query[1]);

        if (i != null && j != null) return ratios[i][j];
        if (i == null && j == null && query[0].equals(query[1])) return 1.0;
        return NOT_KNOWN;
    }

    private static final double NOT_KNOWN = -1.0; // must be negative
}

final class UnitTest {
    public static void main(final String[] args) {
        final String[][] equations = { {"a", "b"}, {"b", "c"} };

        final double[] values = { 2.0, 3.0 };

        final String[][] queries =
                { {"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"} };

        for (final double result
                : new Solution().calcEquation(equations, values, queries))
            System.out.println(result);
    }

    private UnitTest() { throw new AssertionError(); }
}
