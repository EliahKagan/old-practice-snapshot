using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static int ReadOne() => int.Parse(Console.ReadLine());
    
    private static void ReadPair(out int x, out int y)
    {
        var xy = Console.ReadLine().Split();
        x = int.Parse(xy[0]);
        y = int.Parse(xy[1]);
    }
    
    private static void Connect(this List<int>[] graph, int u, int v)
    {
        if (graph[u] == null) graph[u] = new List<int>();
        graph[u].Add(v);
    }
    
    private static List<int>[] ReadGraph()
    {
        int n, m;
        ReadPair(out n, out m);
        var graph = new List<int>[n + 1];
        
        for (int u, v; m != 0; --m) {
            ReadPair(out u, out v);
            graph.Connect(u, v);
            graph.Connect(v, u);
        }
        
        return graph;
    }
    
    private static int[] BFSFindDepths(this List<int>[] graph, int s)
    {
        var search_depths = Enumerable.Repeat(-1, graph.Length).ToArray();
        
        var queue = new Queue<int>();
        queue.Enqueue(s);
        var depth = 0;
        
        for (int count; (count = queue.Count) != 0; ++depth) {
            do {
                var u = queue.Dequeue();
                
                if (search_depths[u] == -1) {
                    search_depths[u] = depth;

                    if (graph[u] != null)
                        foreach (var v in graph[u]) queue.Enqueue(v);
                }
                
            }
            while (--count != 0);
        }
        
        return search_depths;
    }
    
    // finds the distances from the s-node to each other node, skipping the
    // leading 0-node (graph[0]) as well as the s-node itself (graph[s])
    private static IEnumerable<int> BFSFindDistances(this List<int>[] graph,
                                                     int s)
    {
        const int edge_weight = 6;
        
        var search_depths = graph.BFSFindDepths(s);
        
        foreach (var i in Enumerable.Range(1, graph.Length - 1)) {
            if (i != s) {
                yield return search_depths[i] == -1
                                ? -1
                                : search_depths[i] * edge_weight;
            }
        }
    }
    
    private static void Main()
    {
        for (var q = ReadOne(); q > 0; --q) {
            var graph = ReadGraph();
            var distances = graph.BFSFindDistances(ReadOne());
            Console.WriteLine(string.Join(" ", distances));
        }
    }
}
