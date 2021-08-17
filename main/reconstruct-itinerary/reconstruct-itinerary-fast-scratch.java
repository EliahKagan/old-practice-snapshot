import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.function.Consumer;
import java.util.stream.Stream;

class Solution {
    public List<String> findItinerary(String[][] tickets) {
        // Create the adjacency list.
        final Map<String, List<String>> adj = new HashMap<>();
        for (final String[] edge : tickets) {
            List<String> row = adj.get(edge[0]);
            if (row == null) {
                row = new ArrayList<>();
                adj.put(edge[0], row);
            }
            row.add(edge[1]);
        }

        // Sort each row so items can be popped in lexicographic order.
        final Comparator<String> reverseOrder = Collections.reverseOrder();
        for (final List<String> row : adj.values()) row.sort(reverseOrder);

        // We will build the path backwards.
        final List<String> path = new ArrayList<>();

        // Recursive Hierholzer's algorithm.
        final Consumer<String> dfs = new Consumer<String>() {
            public void accept(final String src) {
                final List<String> row = adj.get(src);
                if (row != null)
                    while (!row.isEmpty()) accept(row.remove(row.size() - 1));
                path.add(src);
            }
        };

        // Build the path and return it forwards.
        dfs.accept("JFK");
        Collections.reverse(path);
        return path;
    }
}

final class UnitTest {
    public static void main(final String[] args) {
        final Solution s = new Solution();

        final String[][] a = {
                { "MUC", "LHR" },
                { "JFK", "MUC" },
                { "SFO", "SJC" },
                { "LHR", "SFO" }
        };

        final String[][] b = {
                { "JFK", "SFO" },
                { "JFK", "ATL" },
                { "SFO", "ATL" },
                { "ATL", "JFK" },
                { "ATL", "SFO" }
        };

        final String[][] c = {
                { "JFK", "KUL" },
                { "JFK", "NRT" },
                { "NRT", "JFK" }
        };

        Stream.of(a, b, c).forEachOrdered(tickets -> {
            System.out.println(String.join(" ", s.findItinerary(tickets)));
        });
    }

    private UnitTest() { throw new AssertionError(); }
}
