<Query Kind="Program" />

public class UndirectedGraphNode {
    public int label;
    public IList<UndirectedGraphNode> neighbors;
    public UndirectedGraphNode(int x) { label = x; neighbors = new List<UndirectedGraphNode>(); }
}

public class Solution {
    public UndirectedGraphNode CloneGraph(UndirectedGraphNode node) {
        if (node == null) return null;
        
        var copies =
                new Dictionary<UndirectedGraphNode, UndirectedGraphNode>();
        
        void CreateUnconnectedCopies(UndirectedGraphNode orig) {
            copies.Add(orig, new UndirectedGraphNode(orig.label));
            
            foreach (var neighbor in orig.neighbors) {
                if (!copies.ContainsKey(neighbor))
                    CreateUnconnectedCopies(neighbor);
            }
        }
        
        void ConnectCopies(UndirectedGraphNode orig) {
            var copy = copies[orig];
            
            foreach (var neighbor in orig.neighbors)
                copy.neighbors.Add(copies[neighbor]);
            
            var degree = copy.neighbors.Count; // == orig.neighbors.Count
            for (var i = 0; i != degree; ++i) {
                if (copy.neighbors[i].neighbors.Count == 0)
                    ConnectCopies(orig.neighbors[i]);
            }
        }
        
        CreateUnconnectedCopies(node);
        ConnectCopies(node);
        return copies[node];
    }
}

private static void Main() { }