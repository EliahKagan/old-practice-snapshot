using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.2.0")]

internal static class Lexer {
    /// <summary>
    /// Reads a line of whitespace-separated tokens and ensures that the
    /// correct numbers of tokens have been read, but allows excess whitespace.
    /// </summary>
    /// <param name="needTokenCount">The number of tokens needed.</param>
    /// <param name="description">What it's for (for error messages).</param>
    /// <returns>An array of strings, one per token read.</returns>
    internal static string[] ReadTokens(int needTokenCount, string description)
    {
        var line = Console.ReadLine();

        var tokens = line.Split((char[])null,
                                StringSplitOptions.RemoveEmptyEntries);

        if (tokens.Length != needTokenCount) {
            throw new FormatException(
                    $"wrong record length while reading {description} "
                        + $"({nameof(needTokenCount)}={needTokenCount}, "
                        + $"{nameof(line)}=\"{line}\")");
        }

        return tokens;
    }

    /// <summary>
    /// Reads a line and interprets it as a single 32-bit signed integer.
    /// </summary>
    /// <returns>The number that was read.</returns>
    internal static int ReadInt32() => int.Parse(Console.ReadLine());
}

/// <summary>
/// A non-reentrant graph implementation representing a Boggle grid.
/// </summary>
internal sealed class GridGraph {
    /// <summary>
    /// Reads a grid from standard input and creates a graph for it.
    /// </summary>
    public GridGraph()
    {
        // Read the grid dimensions.
        var mn = Array.ConvertAll(Lexer.ReadTokens(2, "dimensions"),
                                  int.Parse);
        _m = mn[0];
        _n = mn[1];

        // Read the letters that make up the grid, in row-major order.
        _grid = Array.ConvertAll(Lexer.ReadTokens(_m * _n, "grid"), tok => {
            if (tok.Length != 1)
                throw new FormatException("cell text must be length 1");
            return tok[0];
        });

        // Build the adjacency list.
        _adj = AdjacencyList().ToArray();
        Debug.Assert(_adj.Length == _grid.Length + 1);

        // This on-board visitation list is why a GridGraph isn't thread-safe.
        Vis = new bool[_adj.Length];
    }

    /// <summary>
    /// Gets the character in the cell identified by the specified vertex.
    /// </summary>
    /// <param name="vertex">The vertex identifying the cell.</param>
    /// <returns></returns>
    public char this[int vertex] => _grid[vertex];

    /// <summary>
    /// Gets the row of the adjacency list for the specified vertex.
    /// </summary>
    /// <param name="vertex">The vertex whose neighbors are enumerated.</param>
    /// <returns></returns>
    public IEnumerable<int> Adj(int vertex) => _adj[vertex];

    /// <summary>
    /// Gets the visitation list, whose contents the programmer may modify.
    /// </summary>
    public bool[] Vis { get; }

    /// <summary>
    /// Gets the root of the graph. (Returns the final index.)
    /// </summary>
    public int Root => _grid.Length;

    /// <summary>
    /// Generates all rows of the adjacency list determined by the topology
    /// induced by _m and _n, followed by a final row for a virtual root vertex
    /// with edges to every other vertex.
    /// </summary>
    /// <returns>A sequence of the rows.</returns>
    private IEnumerable<int[]> AdjacencyList()
    {
        for (var i = 0; i != _m; ++i) {
            for (var j = 0; j != _n; ++j)
                yield return AdjacentVertices(i, j).ToArray();
        }

        yield return Enumerable.Range(0, _m * _n).ToArray();
    }

    /// <summary>
    /// Gets valid indices (i.e., vertex numbers) representing positions in the
    /// grid adjacent to the specified coordinates.
    /// </summary>
    /// <param name="i">The row index of the cell being surrounded.</param>
    /// <param name="j">The column index of the cell being surrounded.</param>
    /// <returns>A sequence of the adjacent vertices.</returns>
    private IEnumerable<int> AdjacentVertices(int i, int j)
        => from h in Enumerable.Range(i - 1, 3)
           where 0 <= h && h < _m
           from k in Enumerable.Range(j - 1, 3)
           where 0 <= k && k < _n && (h != i || k != j)
           select h * _n + k;

    private readonly int _m, _n;
    private readonly char[] _grid;
    private readonly int[][] _adj;
}

/// <summary>
/// A prefix tree supporting traversal with a GridGraph, to solve Boggle.
/// </summary>
internal sealed class Trie {
    /// <summary>Adds a word to the trie.</summary>
    /// <param name="word">The word to be added.</param>
    public void Add(string word)
    {
        var cur = this;

        foreach (var ch in word) {
            Trie next;
            if (!cur._children.TryGetValue(ch, out next)) {
                next = new Trie();
                cur._children.Add(ch, next);
            }

            cur = next;
        }

        cur._word = word;
    }

    /// <summary>
    /// Finds all words that can be produced by adjacent letters in a given
    /// GridGraph, with each vertex used only oce per word.
    /// </summary>
    /// <param name="graph">
    /// The GridGraph object to be traversed along with this Trie.</param>
    /// <returns>A lexicographically ordered set of matching words.</returns>
    public SortedSet<string> Search(GridGraph graph)
    {
        var acc = new SortedSet<string>(StringComparer.Ordinal);
        Dfs(graph, acc, graph.Root);
        return acc;
    }

    /// <summary>
    /// Helper function for Search. Performs depth-first search of the graph
    /// while traversing the trie, following only paths both permit.
    /// </summary>
    /// <param name="graph">The graph being searched.</param>
    /// <param name="acc">A set, to accumulate matching strings.</param>
    /// <param name="v">The starting vertex for the search.</param>
    private void Dfs(GridGraph graph, SortedSet<string> acc, int v)
    {
        if (_word != null) acc.Add(_word);

        if (_children.Count != 0) {
            graph.Vis[v] = true;

            foreach (var w in graph.Adj(v)) {
                if (!graph.Vis[w]) {
                    Trie child;
                    if (_children.TryGetValue(graph[w], out child))
                        child.Dfs(graph, acc, w);
                }
            }

            graph.Vis[v] = false;
        }
    }

    private string _word = null;

    private readonly Dictionary<char, Trie> _children =
            new Dictionary<char, Trie>();
}

internal static class Solution {
    private static void Main()
    {
        for (var t = Lexer.ReadInt32(); t > 0; --t) {
            var trie = new Trie();
            foreach (var word in ReadWords()) trie.Add(word);

            var graph = new GridGraph(); 
            var matches = trie.Search(graph);

            Console.WriteLine(matches.Count == 0 ? "-1"
                                                 : string.Join(" ", matches));
        }
    }

    /// <summary>
    /// Reads the words that will be added to the trie.
    /// </summary>
    /// <returns>An array of the words that were read.</returns>
    private static string[] ReadWords()
        => Lexer.ReadTokens(Lexer.ReadInt32(), "word list");
}
