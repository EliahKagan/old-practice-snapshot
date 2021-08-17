using System;
using System.Collections.Generic;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal sealed class DisjointSets {
    internal DisjointSets(int size)
    {
        _parents = new int[size];
        for (var i = 0; i != size; ++i) _parents[i] = i;

        _ranks = new int[size];
    }

    /// <summary>Checks if sets are separate, and joins them if so.</summary>
    /// <param name="i">Any element of the first set.</param>
    /// <param name="j">Any element of the second set.</param>
    /// <returns>True if the two sets were separate, false otherwise.</returns>
    internal bool Union(int i, int j)
    {
        // find the ancestors and stop if they are already the same
        i = FindSet(i);
        j = FindSet(j);
        if (i == j) return false;

        // unite by rank
        if (_ranks[i] < _ranks[j]) {
            _parents[i] = j;
        } else {
            if (_ranks[i] == _ranks[j]) ++_ranks[i];
            _parents[j] = i;
        }

        return true;
    }

    private int FindSet(int i)
    {
        // find the ancestor
        var j = i;
        while (j != _parents[j]) j = _parents[j];

        // compress the path
        while (i != j) {
            var next = _parents[i];
            _parents[i] = j;
            i = next;
        }

        return j;
    }

    private readonly int[] _parents, _ranks;
}

internal struct Edge : IComparable<Edge> {
    internal Edge(int u, int v, int wt)
    {
        U = u;
        V = v;
        Wt = wt;
    }

    public int CompareTo(Edge other) => Wt.CompareTo(other.Wt);

    internal int U { get; }
    internal int V { get; }
    internal int Wt { get; }
}

/// <summary>Minheap extension methods for List.</summary>
internal static class HeapQ {
    internal static void Heapify<T>(this List<T> self) where T : IComparable<T>
    {
        for (var parent = self.Count / 2; parent >= 0; --parent)
            self.SiftDown(parent);
    }

    internal static T HeapPop<T>(this List<T> self) where T : IComparable<T>
    {
        var ret = self[0];
        var last = self.Count - 1;

        if (last == 0) {
            self.Clear();
        } else {
            self[0] = self[last];
            self.RemoveAt(last);
            self.SiftDown(0);
        }

        return ret;
    }

    private const int NoChild = -1;

    private static void SiftDown<T>(this List<T> self, int parent)
            where T : IComparable<T>
    {
        for (; ; ) {
            var child = self.PickChild(parent);
            if (child == NoChild || self.OrderOK(parent, child)) break;

            self.Swap(parent, child);
            parent = child;
        }
    }

    private static int PickChild<T>(this List<T> self, int parent)
            where T : IComparable<T>
    {
        var left = parent * 2 + 1;
        if (left >= self.Count) return NoChild;

        var right = left + 1;
        return right == self.Count || self.OrderOK(left, right) ? left : right;
    }

    private static void Swap<T>(this List<T> self, int parent, int child)
    {
        var tmp = self[parent];
        self[parent] = self[child];
        self[child] = tmp;
    }

    private static bool OrderOK<T>(this List<T> self, int parent, int child)
            where T : IComparable<T>
        => self[parent].CompareTo(self[child]) <= 0;
}

internal static class Solution {
    private static void Main()
    {
        var counts = ReadRecord();
        var vertexCount = counts[0];
        var edgeCount = counts[1];

        Console.WriteLine(ReadEdges(edgeCount).ComputeMstWeight(vertexCount));
    }
    
    /// <summary>Compute total MST weight (mutates edges parameter).</summary>
    /// <param name="edges">A list of edges (which is mutated).</param>
    /// <param name="vertexCount">The number of vertices in this graph.</param>
    /// <returns>The sum of edge weights in any MST of this graph.</returns>
    private static int ComputeMstWeight(this List<Edge> edges, int vertexCount)
    {
        if (vertexCount < 2) return 0;

        // Add 1 because we are not using vertex 0 (we want 1-based indexing).
        var sets = new DisjointSets(vertexCount + 1);

        // This may save time because we only pop edges until we have an MST.
        edges.Heapify();

        // Pick edges until we have an MST or all edges were considered.
        var weight = 0;
        for (var needed = vertexCount - 1; needed != 0 && edges.Count != 0; ) {
            var edge = edges.HeapPop();

            if (sets.Union(edge.U, edge.V)) {
                weight += edge.Wt;
                --needed;
            }
        }

        return weight;
    }

    private static List<Edge> ReadEdges(int edgeCount)
    {
        var edges = new List<Edge>(edgeCount);

        while (edgeCount-- != 0) {
            var u_v_wt = ReadRecord();
            edges.Add(new Edge(u_v_wt[0], u_v_wt[1], u_v_wt[2]));
        }

        return edges;
    }

    private static int[] ReadRecord()
        => Array.ConvertAll(Console.ReadLine().Split((char[])null,
                            StringSplitOptions.RemoveEmptyEntries), int.Parse);
}
