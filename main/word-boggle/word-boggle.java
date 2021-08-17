import java.util.Arrays;
import java.util.HashMap;
import java.util.InputMismatchException;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;
import java.util.stream.IntStream;

/** A non-reentrant graph implementation representing a Boggle grid. */
final class GridGraph {
    /** Reads a grid and creates a graph for it.
     * @param sc    A Scanner used to read grid data. */
    GridGraph(final Scanner sc)
    {
        // Create an unpopulated grid.
        _m = sc.nextInt();
        _n = sc.nextInt();
        _grid = new char[_m * _n];

        // Read data from the scanner to populate the grid.
        for (int v = 0; v != _grid.length; ++v) {
            final String tok = sc.next();
            if (tok.length() != 1)
                throw new InputMismatchException("cell text must be length 1");
            _grid[v] = tok.charAt(0);
        }

        // The graph's topology will be determined by the grid dimensions...
        _adj = new int[_grid.length + 1][];
        int v = 0;
        for (int i = 0; i != _m; ++i)
            for (int j = 0; j !=  _n; ++j) _adj[v++] = adjacentVertices(i, j);

        // ...but with a final vertex: a virtual root with edges to each cell.
        assert v == _grid.length;
        _adj[v] = IntStream.range(0, _grid.length).toArray();

        // This on-board visitation list is why GridGraph isn't thread-safe.
        vis = new boolean[_adj.length];
    }

    /** Gets the character at the specified vertex.
     * @param vertex    The index (vertex number) in the flattened grid.
     * @return          The character in the cell represented by the vertex. */
    char grid(final int vertex)
    {
        return _grid[vertex];
    }

    /** Gets the vertices adjacent to the specified vertex.
     * @param vertex    The vertex whose adjacency-list row is looked up.
     * @return          An IntStream of the neighboring vertices. */
    IntStream adj(final int vertex)
    {
        return Arrays.stream(_adj[vertex]);
    }

    /** Gets the root of the graph, a virtual vertex connecting to all others.
     * @return      The virtual root vertex, which is just the last index. */
    int root()
    {
        assert _grid.length == _adj.length - 1;
        return _grid.length;
    }

    /** Gets valid indices (i.e., vertex numbers) representing positions in the
     * grid adjacent to the specified coordinates.
     * @param i     The row index of the cell whose adjacents are sought.
     * @param j     The column index of the cell whose adjacents are sought.
     * @return      A newly created array of the adjacent vertices. */
    private int[] adjacentVertices(final int i, final int j)
    {
        return adjacentRange(i).filter(h -> 0 <= h && h < _m)
                .flatMap(h -> adjacentRange(j).filter(k -> 0 <= k && k < _n
                                                        && (h != i || k != j))
                                              .map(k -> h * _n + k))
                .toArray();
    }

    /** Gets the range of three indices centered at the specified position.
     * @param index     The index for which we get [index - 1, index + 1].
     * @return          An IntStream of the three indices in the range. */
    private static IntStream adjacentRange(final int index)
    {
        return IntStream.rangeClosed(index - 1, index + 1);
    }

    private final int _m, _n;
    private final char[] _grid;
    private final int[][] _adj;

    /** The visitation list, whose contents the programmer may modify. */
    final boolean[] vis;
}

/** A prefix tree supporting traversal with a GridGraph, to solve Boggle.
 * @see     GridGraph */
final class Trie {
    /** Adds a word to the trie.
     * @param word  The word to be added. */
    void add(final String word)
    {
        Trie node = this;

        for (int pos = 0; pos != word.length(); ++pos) {
            final char ch = word.charAt(pos);
            node = node._children.computeIfAbsent(ch, key -> new Trie());
        }

        node._word = word;
    }

    /** Finds all words that can be produced by adjacent letters in a given
     * GridGraph, with each vertex used only once per word.
     * @param graph The GridGraph object to be traversed along with this Trie.
     * @return      A set of matching words, which iterates lexicographically.
     * @see         GridGraph */
    Set<String> search(final GridGraph graph)
    {
        final Set<String> acc = new TreeSet<>();
        dfs(graph, acc, graph.root());
        return acc;
    }

    /** Helper function for search. Performs depth-first search of the graph
     * while traversing the trie, following only paths both permit.
     * @param graph     The graph being searched.
     * @param acc       A set, into which matching strings are accumulated.
     * @param v         The starting vertex for the search. */
    private void dfs(final GridGraph graph, final Set<String> acc, final int v)
    {
        if (_word != null) acc.add(_word);

        if (!_children.isEmpty()) {
            graph.vis[v] = true;

            graph.adj(v).forEachOrdered(w -> {
                if (!graph.vis[w]) {
                    final Trie child = _children.get(graph.grid(w));
                    if (child != null) child.dfs(graph, acc, w);
                }
            });

            graph.vis[v] = false;
        }
    }

    private String _word = null;
    private final Map<Character, Trie> _children = new HashMap<>();
}

final class Solution {
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) run(sc);
        }
    }

    /** Runs for a single test case.
     * @param sc    The Scanner from which input is read. */
    private static void run(final Scanner sc)
    {
        final Trie trie = new Trie();
        for (int x = sc.nextInt(); x > 0; --x) trie.add(sc.next());

        final GridGraph graph = new GridGraph(sc);
        final Set<String> matches = trie.search(graph);

        System.out.println(matches.isEmpty() ? "-1"
                                             : String.join(" ", matches));
    }

    private Solution() { throw new AssertionError(); }
}
