#define DEBUG

using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Text.RegularExpressions;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static void Main()
    {
        for (var t = Get(); t > 0; --t) {
            var adj = GetGraph();
            var start = Get();
            PrintCosts(Dijkstra(adj, start), start);
        }
    }

    private static List<OutEdge>[] GetGraph()
    {
        var adj = new List<OutEdge>[Get() + 1]; // add one for 1-based indexing
        for (var i = 0; i != adj.Length; ++i) adj[i] = new List<OutEdge>();

        for (var edgeCount = Get(); edgeCount > 0; --edgeCount) {
            var u = Get();
            var v = Get();
            var weight = Get();

            adj[u].Add(new OutEdge(v, weight));
            adj[v].Add(new OutEdge(u, weight));
        }

        return adj;
    }

    private static int[] Dijkstra(List<OutEdge>[] adj, int start)
    {
        var costs = new int[adj.Length];
        for (var i = 0; i != costs.Length; ++i) costs[i] = Infinity;
        costs[start] = 0;

        var heap = new SortedSet<Entry>();
        heap.Add(new Entry(start, 0));

        while (heap.Count != 0) {
            var ent = heap.Min;
            heap.Remove(ent);
            Contract.Assert(costs[ent.Vertex] == ent.Cost);

            foreach (var edge in adj[ent.Vertex]) {
                var newCost = ent.Cost + edge.Weight;
                if (costs[edge.Dest] <= newCost) continue;

                heap.Remove(new Entry(edge.Dest, costs[edge.Dest]));
                heap.Add(new Entry(edge.Dest, newCost));
                costs[edge.Dest] = newCost;
            }
        }

        return costs;
    }

    private static void PrintCosts(int[] costs, int start)
    {
        var values = from i in Enumerable.Range(1, costs.Length - 1)
                     where i != start
                     select costs[i] == Infinity ? NoPath : costs[i];

        Console.WriteLine(string.Join(" ", values));
    }

    private static int Get()
    {
        s_en.MoveNext();
        return int.Parse(((Match)s_en.Current).Value);
    }

    private static readonly IEnumerator s_en =
            new Regex(@"\S+", RegexOptions.Compiled)
                .Matches(Console.In.ReadToEnd())
                .GetEnumerator();

    private const int Infinity = int.MaxValue;

    private const int NoPath = -1;
}

internal struct OutEdge {
    internal OutEdge(int dest, int weight)
    {
        Dest = dest;
        Weight = weight;
    }

    internal int Dest { get; }

    internal int Weight { get; }
}

internal struct Entry : IComparable<Entry> {
    internal Entry(int vertex, int cost)
    {
        Vertex = vertex;
        Cost = cost;
    }

    public int CompareTo(Entry other)
    {
        var byCost = Cost.CompareTo(other.Cost);
        return byCost != 0 ? byCost : Vertex.CompareTo(other.Vertex);
    }

    internal int Vertex { get; }

    internal int Cost { get; }
}
