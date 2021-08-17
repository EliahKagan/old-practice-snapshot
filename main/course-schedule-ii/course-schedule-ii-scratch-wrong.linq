<Query Kind="Program" />

public class Solution {
    public int[] FindOrder(int numCourses, int[,] prerequisites)
    {
        var adj = BuildAdjacencyList(numCourses, prerequisites);
        var res = ReverseTopologicalSort(adj);
        return res == null ? new int[0] : res.ToArray();
    }
    
    private static List<int>[] BuildAdjacencyList(int vertexCount,
                                                  int[,] edges)
    {
        var adj = new List<int>[vertexCount];
        for (var i = 0; i != vertexCount; ++i) adj[i] = new List<int>();
        
        for (var i = 0; i != edges.GetLength(0); ++i) {
            adj[edges[i, 0]].Add(edges[i, 1]);
            adj[edges[i, 1]].Add(edges[i, 0]);
        }
        
        return adj.Dump("adjacency list");
    }
    
    // Returns the reverse of a topological ordering of the graph represented
    // by the adajacency list, adj. Or if the graph is cyclic, returns null.
    private static List<int> ReverseTopologicalSort(List<int>[] adj)
    {
        var res = new List<int>(adj.Length);
        var vis = new Color[adj.Length];
        
        bool HasCycleFrom(int src) {
            switch (vis[src.Dump("vertex")].Dump("color")) {
            case Color.White:
                vis[src] = Color.Gray;
                if (adj[src].Any(HasCycleFrom)) return true;
                vis[src] = Color.Black;
                res.Add(src);
                return false;

            case Color.Gray:
                return true;

            case Color.Black:
                return false;
            }
            
            throw new InvalidOperationException("invalid visitation state");
        }
        
        return Enumerable.Range(0, adj.Length).Any(HasCycleFrom) ? null : res;
    }
    
    // Visitation states for traversing a directed graph.
    private enum Color {
        White,  // unvisited (this must appear first)
        Gray,   // visited but not fully explored
        Black   // fully explored
    }
}

internal static class UnitTest {
    private static void Main()
    {
        var s = new Solution();
        s.FindOrder(2, new[,] {{1, 0}}).Dump();
    }
}
