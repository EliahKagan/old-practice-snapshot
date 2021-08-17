import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.function.Predicate;
import java.util.stream.Stream;

class Solution {
    private static final class AdjInfo {
        AdjInfo(final String dest) { this.dest = dest; }

        final String dest;
        boolean visited = false;
    }

    public List<String> findItinerary(final String[][] tickets) {
        // Create an empty adjacency list.
        final Map<String, List<AdjInfo>> adj = new HashMap<>();

        // Populate the adjacency list.
        for (final String[] edge : tickets) {
            List<AdjInfo> row = adj.get(edge[0]);
            if (row == null) {
                row = new ArrayList<>();
                adj.put(edge[0], row);
            }
            row.add(new AdjInfo(edge[1]));
        }

        // Sort each row lexicographically.
        for (final List<AdjInfo> row : adj.values())
            row.sort(Comparator.comparing(info -> info.dest));

        // We will use the target length and the current path in the search.
        final int length = tickets.length + 1;
        final List<String> path = new ArrayList<>();

        // We will search in lexicographic order until a full path is found.
        final Predicate<String> dfs = new Predicate<String>() {
            @Override
            public boolean test(final String src) {
                path.add(src);
                if (path.size() == length) return true;

                final List<AdjInfo> row = adj.get(src);
                if (row != null) {
                    for (final AdjInfo info : row) {
                        if (!info.visited) {
                            info.visited = true;
                            if (test(info.dest)) return true;
                            info.visited = false;
                        }
                    }
                }

                path.remove(path.size() - 1);
                return false;
            }
        };

        // Build and return the itinerary (or an empty list if there is none).
        dfs.test("JFK");
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
