#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

/// <summary>
/// A modified binary minheap, suitable for Prim's and Dijkstra's algorithms.
/// </summary>
internal sealed class PrimHeap {
    internal PrimHeap(int minKey, int maxKey)
    {
        CheckConstructorArguments(minKey, maxKey);

        // Create and populate the [key -> index] map.
        _map = new int[maxKey + 1];
        for (var key = 0; key != minKey; ++key) _map[key] = None;
        var count = 0;
        for (var key = minKey; key != _map.Length; ++key) _map[key] = count++;
        Contract.Assert(count == maxKey - minKey + 1);

        // Create and populate the [index -> (key, value)] list.
        _entries = new List<KeyValuePair<int, int>>(count);
        while (count-- != 0)
            _entries.Add(new KeyValuePair<int, int>(minKey++, int.MaxValue));
        Contract.Assert(minKey == maxKey + 1);
    }

    internal int Count => _entries.Count;

    internal KeyValuePair<int, int> Pop()
    {
        var ret = _entries[0];
        _map[ret.Key] = None;

        var last = Count - 1;

        if (last == 0) {
            _entries.Clear();
        } else {
            _entries[0] = _entries[last];
            _entries.RemoveAt(last);
            SiftDown(0);
        }

        return ret;
    }

    internal void Decrease(int key, int value)
    {
        var child = _map[key];

        if (child != None && value < _entries[child].Value) {
            _entries[child] = new KeyValuePair<int, int>(key, value);
            SiftUp(child);
        }
    }

    private const int None = -1;

    private static void CheckConstructorArguments(int minKey, int maxKey)
    {
        if (minKey < 0) {
            throw new ArgumentOutOfRangeException(
                    paramName: nameof(minKey),
                    message: $"{nameof(minKey)} can't be negative");
        }

        if (minKey > maxKey) {
            throw new ArgumentException(
                    paramName: nameof(minKey),
                    message: $"{nameof(minKey)} can't exceed {nameof(maxKey)}"
                );
        }
    }

    private void SiftUp(int child)
    {
        while (child != 0) {
            var parent = (child - 1) / 2;
            if (OrderOK(parent, child)) break;

            Swap(child, parent);
            child = parent;
        }

        Record(child);
    }

    private void SiftDown(int parent)
    {
        for (; ; ) {
            var child = PickChild(parent);
            if (child == None || OrderOK(parent, child)) break;

            Swap(parent, child);
            parent = child;
        }

        Record(parent);
    }

    private int PickChild(int parent)
    {
        var left = parent * 2 + 1;
        if (left >= Count) return None;

        var right = left + 1;
        return right == Count || OrderOK(left, right) ? left : right;
    }

    private void Swap(int src, int dest)
    {
        var tmp = _entries[dest];
        _entries[dest] = _entries[src];
        _entries[src] = tmp;

        Record(src);
    }

    private void Record(int src)
        => _map[_entries[src].Key] = src;

    private bool OrderOK(int parent, int child)
        => _entries[parent].Value <= _entries[child].Value;

    // key -> index
    private readonly int[] _map;

    // index -> (key, value)
    private readonly List<KeyValuePair<int, int>> _entries;
}

/// <summary>
/// A pair of vertices representing the endpoints of an undirected graph.
/// </summary>
internal struct Endpoints : IEquatable<Endpoints> {
    internal Endpoints(int u, int v)
    {
        if (u > v) {
            V = u;
            U = v;
        } else {
            U = u;
            V = v;
        }
    }

    public bool Equals(Endpoints other)
        => U == other.U && V == other.V;

    public override bool Equals(object other)
        => Equals((Endpoints)other);

    public override int GetHashCode()
        => (17 * 31 + U) * 31 + V;

    internal int U { get; }
    internal int V { get; }
}

internal struct Neighbor {
    internal Neighbor(int dest, int wt)
    {
        Dest = dest;
        Wt = wt;
    }

    internal int Dest { get; }
    internal int Wt { get; }
}

internal static class Solution {
    /// <summary>The lowest vertex number used.</summary>
    private const int FirstVertex =  1;

    /// <summary>
    /// The value to show as the "cost" to reach an unreachable vertex.
    /// </summary>
    private const int UnreachableCost = -1;

    private static void Main()
    {
        for (var t = ReadValue(); t > 0; --t) {
            var adj = ReadGraph();
            var start = ReadValue();

            var costs = adj.ComputeShortestReaches(start);

            var vertices = Enumerable.Range(FirstVertex,
                                            adj.Count - FirstVertex);

            Console.WriteLine(string.Join(" ", from dest in vertices
                                               where dest != start
                                               select costs[dest]));
        }
    }

    private static int ReadValue() => int.Parse(Console.ReadLine());

    private static int[] ReadRecord()
    {
        var line = Console.ReadLine();

        var tokens = line.Split((char[])null,
                                StringSplitOptions.RemoveEmptyEntries);

        return Array.ConvertAll(tokens, int.Parse);
    }

    /// <summary>
    /// Reads a weighted directed graph as an adjacency list.
    /// </summary>
    private static List<List<Neighbor>> ReadGraph()
    {
        var vertexCount_edgeCount = ReadRecord();
        var vertexCount = vertexCount_edgeCount[0];
        var edgeCount = vertexCount_edgeCount[1];

        var adj = GetEmptyAdjacencyList(vertexCount);

        foreach (var edge in ReadSimpleGraphEdges(edgeCount)) {
            var u = edge.Key.U;
            var v = edge.Key.V;
            var wt = edge.Value;

            adj[u].Add(new Neighbor(v, wt));
            adj[v].Add(new Neighbor(u, wt));
        }

        return adj;
    }

    /// <summary>Creates an adjacency list with all rows empty.</summary>
    private static List<List<Neighbor>> GetEmptyAdjacencyList(int vertexCount)
    {
        if (vertexCount < 0) {
            throw new ArgumentOutOfRangeException(
                paramName: nameof(vertexCount),
                message: "a graph can't have negatively many vertices");
        }

        var size = FirstVertex + vertexCount;

        var adj = new List<List<Neighbor>>(size);
        for (var n = FirstVertex; n != 0; --n) adj.Add(null);
        while (vertexCount-- != 0) adj.Add(new List<Neighbor>());

        Contract.Assert(adj.Count == size);
        return adj;
    }

    /// <summary>
    /// Reads a graph as a hash-based sparse adjacency matrix.
    /// </summary>
    private static Dictionary<Endpoints, int>
    ReadSimpleGraphEdges(int edgeCount)
    {
        if (edgeCount < 0) {
            throw new ArgumentOutOfRangeException(
                paramName: nameof(edgeCount),
                message: "can't read negatively many edges");
        }

        var edges = new Dictionary<Endpoints, int>();

        while (edgeCount-- != 0) {
            var u_v_wt = ReadRecord();
            var u = u_v_wt[0];
            var v = u_v_wt[1];

            if (u == v) continue;

            var uv = new Endpoints(u, v);
            var wt = u_v_wt[2];

            int oldWt;
            if (!edges.TryGetValue(uv, out oldWt) || wt < oldWt)
                edges[uv] = wt;
        }

        return edges;
    }

    /// <summary>
    /// Calculates the least cost paths from a given starting vertex to each
    /// vertex in a graph, using Dijkstra's algorithm.
    /// </summary>
    /// <param name="adj">The graph to traverse, as an adjacency list.</param>
    /// <param name="start">The vertex where the traversal begins.</param>
    /// <returns>
    /// An array, <c>costs</c>, where <c>costs[index]</c> is the least cost to
    /// traverse from the vertex <c>start</c> to the vertex <c>index</c>.
    /// </returns>
    private static int[] ComputeShortestReaches(this List<List<Neighbor>> adj,
                                                int start)
    {
        var costs = new int[adj.Count];
        for (var i = 0; i != costs.Length; ++i) costs[i] = UnreachableCost;

        var costHeap = new PrimHeap(FirstVertex, adj.Count - 1);
        costHeap.Decrease(start, 0);

        while (costHeap.Count != 0) {
            var ent = costHeap.Pop();
            if (ent.Value == int.MaxValue) break;

            costs[ent.Key] = ent.Value;

            foreach (var neighbor in adj[ent.Key])
                costHeap.Decrease(neighbor.Dest, ent.Value + neighbor.Wt);
        }

        return costs;
    }
}
