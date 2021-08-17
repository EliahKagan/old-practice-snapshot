<Query Kind="Program" />

public class Solution {
    public int[] FindOrder(int numCourses, int[,] prerequisites)
    {
        var graph = new Graph(numCourses, AsDependencyEdges(prerequisites));
        var res = graph.TopologicalSort();
        return res == null ? new int[0] : res.ToArray();
    }
    
    private static IEnumerable<(int, int)>
    AsDependencyEdges(int[,] prerequisites)
        => from i in Enumerable.Range(0, prerequisites.GetLength(0))
           select (prerequisites[i, 1], prerequisites[i, 0]);
}

internal sealed class Graph {
    internal Graph(int vertexCount, IEnumerable<(int, int)> edges)
    {
        _adj = new List<int>[vertexCount];
        for (var i = 0; i != vertexCount; ++i) _adj[i] = new List<int>();
        
        _inorders = new int[vertexCount];
        
        foreach (var (src, dest) in edges) {
            _adj[src].Add(dest);
            ++_inorders[dest];
        }
    }
    
    // If the graph represented by the adjacency list, adj, is acyclic, returns
    // a topological ordering of it. If the graph is cyclic, returns null.
    internal List<int> TopologicalSort()
    {
        if (_used) throw new InvalidOperationException("already toposorted");
        _used = true;
    
        var res = new List<int>(_adj.Length);
        
        for (var roots = new Queue<int>(FindRoots()); roots.Count != 0; ) {
            var src = roots.Dequeue();
            res.Add(src);
            
            foreach (var dest in _adj[src])
                if (--_inorders[dest] == 0) roots.Enqueue(dest);
        }
        
        return res.Count == _adj.Length ? res : null;
    }
    
    private IEnumerable<int> FindRoots()
        => Enumerable.Range(0, _adj.Length).Where(i => _inorders[i] == 0);

    readonly List<int>[] _adj;
    readonly int[] _inorders;
    bool _used = false;
}

internal static class UnitTest {
    private static void Main()
    {
        var s = new Solution();
        s.FindOrder(2, new[,] {{1, 0}}).Dump();
    }
}
