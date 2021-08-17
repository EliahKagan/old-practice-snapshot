<Query Kind="Program" />

public class Solution {
    public bool CanFinish(int numCourses, int[,] prerequisites) {
        if (numCourses < 0) {
            throw new ArgumentOutOfRangeException(nameof(numCourses),
                    "can't have a negative number of courses");
        }
        
        // All courses can be taken if there are no prerequisite cycles.
        return !HasCycle(BuildAdjacencyList(numCourses, prerequisites));
    }
    
    private static List<int>[] BuildAdjacencyList(int numCourses,
                                                  int[,] prerequisites) {
        // Create an empty adjacency list.
        var adj = new List<int>[numCourses];
        for (var i = 0; i != numCourses; ++i) adj[i] = new List<int>();
        
        // Populate the adjacency list.
        for (var i = 0; i != prerequisites.GetLength(0); ++i)
            adj[prerequisites[i, 1]].Add(prerequisites[i, 0]);
        
        return adj;
    }
    
    private static bool HasCycle(List<int>[] adj) {
        // Create an empty visitation list.
        var vis = new Color[adj.Length];
        
        // Look for a cycle from every totally unvisited ("White") vertex.
        for (int start = 0; start != vis.Length; ++start)
            if (HasCycleFrom(adj, vis, start)) return true;
        
        return false;
    }
    
    private static bool HasCycleFrom(List<int>[] adj, Color[] vis, int start) {
        switch (vis[start]) {
        case Color.White:
            vis[start] = Color.Gray;
            
            foreach (var neighbor in adj[start])
                if (HasCycleFrom(adj, vis, neighbor)) return true;
            
            vis[start] = Color.Black;
            
            return false;
        
        case Color.Gray:
            return true;
        
        case Color.Black:
            return false;
        }
        
        throw new NotSupportedException("unreachable code");
    }
    
    private enum Color { White, Gray, Black }
}

internal static class UnitTest {
    private static void Main() {
        "Should be true...".Dump();
        Test(6, new[,] {{0,1}, {0,2}, {1,2}, {2,3}, {1,5}, {2,5}, {4,0}, {4,5}});
        
        "Should be false...".Dump();
        Test(6, new[,] {{0,1}, {0,2}, {1,2}, {2,3}, {1,5}, {2,5}, {4,0}, {4,5}, {3,4}});
    }

    private static void Test(int numCourses, int[,] prerequisites) {
        numCourses.Dump(nameof(numCourses));
        prerequisites.Dump(nameof(prerequisites));
        
        new Solution().CanFinish(numCourses, prerequisites)
                      .Dump("Can finish?");
    }
}
