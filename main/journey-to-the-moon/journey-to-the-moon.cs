using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.1")]

internal static class Graph {
    private static void Get(out int first, out int second)
    {
        var tok = Console.ReadLine().Split();

        first = int.Parse(tok[0]);
        second = int.Parse(tok[1]);
    }

    private static void
    AddAdjacentNode(this Dictionary<int, List<int>> graph, int i, int j)
    {
        List<int> adj;
        if (!graph.TryGetValue(i, out adj))
            graph.Add(i, adj = new List<int>());

        adj.Add(j);
    }

    private static void
    AddEdge(this Dictionary<int, List<int>> graph, int i, int j)
    {
        graph.AddAdjacentNode(i, j);
        graph.AddAdjacentNode(j, i);
    }

    internal static Dictionary<int, List<int>> ReadGraph(out int n)
    {
        int p;
        Get(out n, out p);
        var graph = new Dictionary<int, List<int>>(n);

        for (int i, j; p > 0; --p) {
            Get(out i, out j);
            graph.AddEdge(i, j);
        }

        return graph;
    }
}

internal static class Search {
    private static Stack<int> GetStack(int seed)
    {
        var s = new Stack<int>();
        s.Push(seed);
        return s;
    }

    private static long  // removes a disjoint set; returns its cardinality
    DepthFirstSearch(this Dictionary<int, List<int>> graph, int i)
    {
        var c = 0; // counts nodes as they are removed from the disjoint set
        
        for (var s = GetStack(i); s.Count != 0; ) {
            List<int> adj;
            if (graph.TryGetValue(i = s.Pop(), out adj)) {
                graph.Remove(i);
                ++c;
                foreach (var j in adj) s.Push(j);
            }
        }

        return c;
    }

    private static IEnumerable<long> // removes each disjoint set from graph
    GetDisjointCardinalities(Dictionary<int, List<int>> graph)
    {
        while (graph.Count != 0)
            yield return graph.DepthFirstSearch(graph.First().Key);
    }

    private static long CountSingletonChoices(long sum, long k)
    {
        Trace.Assert(k >= 0L);
        return sum * k + k * (k - 1L) / 2L;
    }

    internal static long
    CountChoices(this Dictionary<int, List<int>> graph, int n)
    {
        var sum = 0L;
        var choices = 0L;

        // count non-singleton choices
        foreach (var c in GetDisjointCardinalities(graph)) {
            choices += sum * c;
            sum += c;
        }

        return choices + CountSingletonChoices(sum, n - sum);
    }
}

internal static class Solution {
    private static void Main()
    {
        int n;
        Console.WriteLine(Graph.ReadGraph(out n).CountChoices(n));
    }
}
