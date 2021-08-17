<Query Kind="Program" />

public class Solution {
    public IList<string> FindItinerary(string[,] tickets) {
        // Create the adjacency list.
        var adj = new Dictionary<string, List<string>>();
        foreach (var i in Enumerable.Range(0, tickets.GetLength(0))) {
            var src = tickets[i, 0];
            if (!adj.TryGetValue(src, out var row)) {
                row = new List<String>();
                adj.Add(src, row);
            }
            row.Add(tickets[i, 1]);
        }
        
        // Sort each row so items can be popped in lexicographic order.
        foreach (var row in adj.Values) row.Sort((s, t) => t.CompareTo(s));
        
        // We will build the path backwards.
        var path = new List<string>();
        
        // Recursive Hierholzer's algorithm.
        void Dfs(string src) {
            if (adj.TryGetValue(src, out var row)) {
                while (row.Count != 0) {
                    var dest = row[row.Count - 1];
                    row.RemoveAt(row.Count - 1);
                    Dfs(dest);
                }
            }
            
            path.Add(src);
        }
        
        // Build the path and return it forwards.
        Dfs("JFK");
        path.Reverse();
        return path;
    }
}

private static void Main() {
    var s = new Solution();
    
    string[,] a = {
        { "MUC", "LHR" },
        { "JFK", "MUC" },
        { "SFO", "SJC" },
        { "LHR", "SFO" }
    };
    
    string[,] b = {
        { "JFK", "SFO" },
        { "JFK", "ATL" },
        { "SFO", "ATL" },
        { "ATL", "JFK" },
        { "ATL", "SFO" }
    };
    
    string[,] c = {
        { "JFK", "KUL" },
        { "JFK", "NRT" },
        { "NRT", "JFK" }
    };
    
    foreach (var tickets in new[] { a, b, c })
        s.FindItinerary(tickets).Dump();
}
