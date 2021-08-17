<Query Kind="Program" />

public class Solution {
    private struct Element {
        internal int Parent, Rank;
    }

    public int[] FindRedundantConnection(int[,] edges) {
        var n = edges.GetLength(0);
    
        var elems = new Element[n + 1];
        foreach (var i in Enumerable.Range(1, n)) elems[i].Parent = i;
        
        int FindSet(int i) {
            if (elems[i].Parent != i) elems[i].Parent = FindSet(elems[i].Parent);
            return elems[i].Parent;
        }
        
        bool Union(int i, int j) { // returns true iff they were separate
            i = FindSet(i);
            j = FindSet(j);
            if (i == j) return false;
            
            if (elems[i].Rank < elems[j].Rank) {
                elems[i].Parent = j;
            } else {
                if (elems[i].Rank == elems[j].Rank) ++elems[i].Rank;
                elems[j].Parent = i;
            }
            
            return true;
        }
        
        var k = 0;
        while (Union(edges[k, 0], edges[k, 1])) ++k;
        return new[] { edges[k, 0], edges[k, 1] };
    }
}

private static void Main() {
     var s = new Solution();
     s.FindRedundantConnection(new[,] { { 1, 2 }, { 1, 3 }, { 2, 3 } }).Dump();
     s.FindRedundantConnection(new[,] { { 1, 2 }, { 2, 3 }, { 3, 4 }, { 1, 4 }, { 1, 5 } }).Dump();
}
