<Query Kind="Program" />

internal sealed class DisjointSets {
    internal DisjointSets(int size)
    {
        _parents = new int[size];
        for (var i = 0; i != size; ++i) _parents[i] = i;
        
        _ranks = new int[size];
    }
    
    internal int FindSet(int i)
    {
        // find the ancestor
        var j = i;
        while (j != _parents[j]) j = _parents[j];
        
        // compress the path
        while (_parents[i] != j) {
            var next = _parents[i];
            _parents[i] = j;
            i = next;
        }
        
        return j;
    }
    
    internal void Union(int i, int j)
    {
        // find the ancestors and stop if they are already the same
        i = FindSet(i);
        j = FindSet(j);
        if (i == j) return;
        
        // unite by rank
        if (_ranks[i] < _ranks[j]) {
            _parents[i] = j;
        } else {
            if (_ranks[i] == _ranks[j]) ++_ranks[i];
            _parents[j] = i;
        }
    }

    private readonly int[] _parents, _ranks;
}

public class Solution {
    public int SwimInWater(int[,] grid)
    {
        var map = Invert(grid);
        var sets = new DisjointSets(map.Length);
        
        var n = grid.GetLength(0);
        var start = grid[0, 0];
        var end = grid[n - 1, n - 1];
        
        for (var t = 1; ; ++t) {
            var (i, j) = map[t];
            
            if (i != 0) Update(grid, sets, t, i - 1, j);
            if (i != n - 1) Update(grid, sets, t, i + 1, j);
            if (j != 0) Update(grid, sets, t, i, j - 1);
            if (j != n - 1) Update(grid, sets, t, i, j + 1);
            
            if (sets.FindSet(start) == sets.FindSet(end)) return t;
        }
    }
    
    private static (int, int)[] Invert(int[,] grid)
    {
        var n = grid.GetLength(0);
        var map = new (int, int)[n * n];
        
        for (var i = 0; i != n; ++i)
            for (var j = 0; j != n; ++j) map[grid[i, j]] = (i, j);
        
        return map;
    }
    
    private static void Update(int[,] grid, DisjointSets sets, int t,
                               int i, int j)
    {
        var s = grid[i, j];
        if (s < t) sets.Union(s, t);
    }
}

internal static class UnitTest {
    private static void Main()
    {
        var s = new Solution();
        
        var a = new[,] { {0, 2},
                         {1, 3} };
        s.SwimInWater(a).Dump("a time");
        
        var b = new[,] { {0,   1,  2,  3,  4},
                         {24, 23, 22, 21,  5},
                         {12, 13, 14, 15, 16},
                         {11, 17, 18, 19, 20},
                         {10,  9,  8,  7,  6} };
        s.SwimInWater(b).Dump("b time");
    }
}
