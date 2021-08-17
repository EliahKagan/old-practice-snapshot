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
