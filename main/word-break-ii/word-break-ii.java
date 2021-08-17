class Solution {
    private static final class Trie extends HashMap<Character, Trie> { }

    private static final Character END_MARK = null;

    private static Map<Character, Trie> buildTrie(final List<String> words) {
        final Map<Character, Trie> trie = new Trie();

        for (final String word : words) {
            Map<Character, Trie> node = trie;

            for (int i = 0; i != word.length(); ++i)
                node = node.computeIfAbsent(word.charAt(i), key -> new Trie());

            node.put(END_MARK, null);
        }

        return trie;
    }

    private static List<List<Integer>>
    constructInitialGraph(final int textLength) {
        final List<List<Integer>> adj = new ArrayList<>(textLength + 1);
        while (adj.size() != textLength) adj.add(null);
        adj.add(Collections.emptyList());
        return adj;
    }

    private static List<Integer>
    getOrMakeRow(final List<List<Integer>> adj, final int i) {
        List<Integer> row = adj.get(i);

        if (row == null) {
            row = new ArrayList<>();
            adj.set(i, row);
        }

        return row;
    }

    private static List<List<Integer>>
    constructGraph(final String text, final Map<Character, Trie> trie)
    {
        final List<List<Integer>> adj = constructInitialGraph(text.length());

        for (int i = text.length() - 1; i != -1; --i) {
            Map<Character, Trie> node = trie;

            for (int j = i; j != text.length(); ++j) {
                node = node.get(text.charAt(j));
                if (node == null) break;

                if (adj.get(j + 1) != null && node.containsKey(END_MARK))
                    getOrMakeRow(adj, i).add(j + 1);
            }
        }

        return adj;
    }

    private static String
    pathAsString(final String text, final List<Integer> path) {
        final StringBuilder sb = new StringBuilder();

        for (int k = 1; k != path.size(); ++k) {
            if (sb.length() != 0) sb.append(" ");
            sb.append(text.substring(path.get(k - 1), path.get(k)));
        }

        return sb.toString();
    }

    private static List<String>
    enumeratePaths(final String text, final List<List<Integer>> adj) {
        if (adj.get(0) == null) return Collections.emptyList();

        final int end = adj.size() - 1;
        final List<String> allPaths = new ArrayList<>();
        final List<Integer> path = new ArrayList<>();

        final IntConsumer dfs = new IntConsumer() {
            @Override
            public void accept(final int i) {
                path.add(i);

                if (i == end)
                    allPaths.add(pathAsString(text, path));
                else
                    for (int j : adj.get(i)) accept(j);

                path.remove(path.size() - 1);
            }
        };

        dfs.accept(0);
        return allPaths;
    }

    public List<String>
    wordBreak(final String text, final List<String> words) {
        return enumeratePaths(text, constructGraph(text, buildTrie(words)));
    }
}
