using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

/// <summary>An edge in a directed graph.</summary>
internal struct Edge {
    /// <summary>Creates an edge with the specified endpoints.</summary>
    /// <param name="src">The source vertex.</param>
    /// <param name="dest">The detination vertex.</param>
    internal Edge(int src, int dest)
    {
        Src = src;
        Dest = dest;
    }

    /// <summary>The sorurce vertex.</summary>
    internal int Src { get; }

    /// <summary>The destination vertex.</summary>
    internal int Dest { get; }
}

/// <summary>Walks through topological sorts in lexicographic order.</summary>
internal sealed class KahnBacktracker : IEnumerable<IList<int>>,
                                        IEnumerator<IList<int>> {
    /// <summary>Creates a backtracker for the specified graph.</summary>
    /// <param name="order">The number of vertices in the graph.</param>
    /// <param name="edges">The edges of the graph.</param>
    /// <param name="chain">An initial (correct) topological sorting.</param>
    internal KahnBacktracker(int order, IEnumerable<Edge> edges,
                             IEnumerable<int> chain)
    {
        if (order < 0) {
            throw new ArgumentOutOfRangeException(paramName: nameof(order),
                    message: "graph can't have negatively many vertices");
        }

        if (order == 0) {
            throw new ArgumentOutOfRangeException(paramName: nameof(order),
                    message: "implementation doesn't accommodate empty graph");
        }

        // Make an empty adjacency list.
        _adj = new List<int>[order + 1];
        for (int vertex = 1; vertex <= order; ++vertex)
            _adj[vertex] = new List<int>();
        
        // Populate the adjacency list.
        foreach (var edge in edges) _adj[edge.Src].Add(edge.Dest);

        // Make an initial indegree table with no incoming edges to any vertex.
        _indegs = new int[order + 1];

        // Hold a copy of the chain (initial toposort).
        _chain = new Stack<int>(chain);
        if (_chain.Count != order) {
            throw new ArgumentException(paramName: nameof(chain), message:
                    "initial state has wrong length to be a topological sort");
        }
    }

    /// <summary>A KahnBacktracker is its own enumerator.</summary>
    /// <returns>The current object, which is its own enumerator.</returns>
    public IEnumerator<IList<int>> GetEnumerator() => this;

    /// <summary>A copy of the current toposort.</summary>
    public IList<int> Current
    {
        get {
            var ret = _chain.ToList();
            ret.Reverse();
            return ret;
        }
    }

    /// <summary>Tries to go to the lexicographically next toposort.</summary>
    /// <returns>True unless we've reached the lexicographic maximum.</returns>
    public bool MoveNext()
    {
        // Shorten the chain only as much as necessary.
        var src = Retreat();

        if (src == null) {
            //
            return false;
        }
    }

    /// <summary>
    /// Attempts to shorten the chain just enough to replace its tip with a
    /// lexicographically higher vertex.
    /// </summary>
    /// <returns>The vertex that can be inserted at the tip, if any.</returns>
    private int? Retreat()
    {
        while (_chain.Count == 0) {
            var src = PopRootFromChain();
            _roots.Add(src);
            var tail = _roots.GetViewBetween(src + 1, int.MaxValue);

            if (tail.Count != 0) {
                // Put the new src in roots and return the old src.
                var res = tail.First();
                tail.Remove(res);
                return res;
            }
        }

        return null;
    }

    /// <summary>
    /// Lengthens the chain to produce a completed topological sort.
    /// </summary>
    void Advance()
    {
        while (_roots.Count != 0) {
            var src = _roots.First();
            _roots.Remove(src);
            PushRootToChain(src);
        }
    }

    /// <summary>
    /// Pops a vertex from the hcain for subsequet insertion as a root, and
    /// increments its forward neighbors' indegrees.
    /// </summary>
    /// <returns>
    /// The popped vertex, which was previously the tip of the chain.
    /// </returns>
    private int PopRootFromChain()
    {
        var src = _chain.Pop();

        foreach (var dest in _adj[src])
            if (_indegs[dest]++ == 0) _roots.Remove(dest);

        return src;
    }

    /// <summary>
    /// Pushes a presumably just-extracted root to the chain.
    /// </summary>
    /// <param name="src">
    /// The extracted root, which will be the new tip of the chain.
    /// </param>
    private void PushRootToChain(int src)
    {
        foreach (var dest in _adj[src])
            if (--_indegs[dest] == 0) _roots.Add(dest);

        _chain.Push(src);
    }

    System.Collections.IEnumerator
    System.Collections.IEnumerable.GetEnumerator() => GetEnumerator();

    object System.Collections.IEnumerator.Current => Current;

    void System.Collections.IEnumerator.Reset()
        => throw new NotSupportedException();

    void IDisposable.Dispose() { }

    private readonly SortedSet<int> _roots = new SortedSet<int>();
    private readonly List<int>[] _adj;
    private readonly int[] _indegs;
    private readonly Stack<int> _chain;
}

internal static class Solution {
}
