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
        
        for (var i = 0; i != edges.GetLength(0); ++i)
            adj[edges[i, 0]].Add(edges[i, 1]);
        
        return adj;
    }
    
    // Returns the reverse of a topological ordering of the graph represented
    // by the adajacency list, adj. Or if the graph is cyclic, returns null.
    private static List<int> ReverseTopologicalSort(List<int>[] adj)
    {
        var res = new List<int>(adj.Length);
        var vis = new Color[adj.Length];
        var stack = new Stack<Frame>();
        
        bool HasCycleFrom(int start) {
            if (vis[start] == Color.Black) return false;
            
            if (vis[start] != Color.White || stack.Count != 0)
                throw new InvalidOperationException("corrupted state");
            
            for (stack.Push(new Frame(start)); stack.Count != 0; ) {
                var frame = stack.Peek();
                
                if (frame.Index == adj[frame.Vertex].Count) {
                    vis[frame.Vertex] = Color.Black;
                    res.Add(frame.Vertex);
                    stack.Pop();
                    continue;
                }
                
                var dest = adj[frame.Vertex][frame.Index++];
                
                switch (vis[dest]) {
                case Color.White:
                    vis[dest] = Color.Gray;
                    stack.Push(new Frame(dest));
                    continue;
                
                case Color.Gray:
                    return true;
                    
                case Color.Black:
                    continue;
                }
                
                throw new InvalidOperationException("invalid visitation state");
            }
            
            return false;
        }
        
        return Enumerable.Range(0, adj.Length).Any(HasCycleFrom) ? null : res;
    }
    
    // Visitation states for traversing a directed graph depth-first.
    private enum Color {
        White,  // unvisited (this must appear first)
        Gray,   // visited but not fully explored
        Black   // fully explored
    }
    
    // Frame for iteratively implemented recursive depth-first graph traversal.
    private sealed class Frame {
        internal Frame(int vertex) => Vertex = vertex;
    
        internal int Vertex { get; }
        
        internal int Index { get; set; } = 0;
    }
}

internal static class UnitTest {
    private static void Main()
    {
        var s = new Solution();
        s.FindOrder(2, new[,] {{1, 0}}).Dump();
    }
}
