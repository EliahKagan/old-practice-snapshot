<Query Kind="Program">
  <Namespace>System.Diagnostics.Contracts</Namespace>
</Query>

#define DEBUG

internal sealed class DisjointSets {
    internal DisjointSets(int totalSize)
    {
        _parents = new int[totalSize];
        for (int u = 0; u != totalSize; ++u) _parents[u] = u;
        
        _sizes = new int[totalSize];
        for (int u = 0; u != totalSize; ++u) _sizes[u] = 1;
    }
    
    internal int Count => _parents.Length;
    
    internal int GetSize(int u) => _sizes[FindSet(u)];
    
    internal void Union(int u, int v)
    {
        // find the ancestors, and stop if they're already the same
        u = FindSet(u);
        v = FindSet(v);
        if (u == v) return;
        
        // unite by size
        if (_sizes[u] < _sizes[v])
            Join(v, u);
        else
            Join(u, v);
    }
    
    private int FindSet(int u)
    { 
        // find the ancestor
        var v = u;
        while (v != _parents[v]) v = _parents[v];
        
        // compress the path
        while (_parents[u] != v) {
            var next = _parents[u];
            _parents[u] = v;
            u = next;
        }
        
        return v;
    }
    
    private void Join(int parent, int child)
    {
        _sizes[parent] += _sizes[child];
        _parents[child] = parent;
    }
    
    private readonly int[] _parents, _sizes;
}

internal sealed class DisjointCoordinateSets {
    internal DisjointCoordinateSets(int height, int width)
    {
        if (height <= 0)
            throw new ArgumentOutOfRangeException(paramName: nameof(height));
        if (width <= 0)
            throw new ArgumentOutOfRangeException(paramName: nameof(width));
    
        _sets = new DisjointSets(height * width + 1);
        Height = height;
        Width = width;
    }
    
    internal int Height { get; }
    internal int Width { get; }
    
    internal int ReachableCount => _sets.GetSize(Root);
    
    internal void ConnectToRoot(int i, int j)
        => _sets.Union(Root, GetVertex(i, j));
    
    internal void Connect(int ui, int vi, int uj, int vj)
        => _sets.Union(GetVertex(ui, vi), GetVertex(uj, vj));
    
    private int Root => _sets.Count - 1;
    
    private int GetVertex(int i, int j)
    {
        if (i < 0 || i >= Height)
            throw new ArgumentOutOfRangeException(paramName: nameof(i));
        
        if (j < 0 || j >= Width)
            throw new ArgumentOutOfRangeException(paramName: nameof(j));
        
        return i * Width + j;
    }
    
    private readonly DisjointSets _sets;
}

public class Solution {
    public int[] HitBricks(int[][] grid, int[][] hits)
    {
        ApplyRemovals(grid, hits);
        var sets = ConstructSets(grid);
        var reach = sets.ReachableCount;
        
        var dropCounts = new int[hits.Length];
        
        for (var pos = hits.Length - 1; pos != -1; --pos) {
            if (hits[pos] == null) continue;
            
            Add(grid, sets, hits[pos][0], hits[pos][1]);
            
            var newReach = sets.ReachableCount;
            dropCounts[pos] = newReach - reach - 1;
            Contract.Assert(dropCounts[pos] >= 0);
            
            reach = newReach;
        }
        
        return dropCounts;
    }
    
    private static void ApplyRemovals(int[][] grid, int[][] hits)
    {
        for (var pos = 0; pos != hits.Length; ++pos) {
            var i = hits[pos][0];
            var j = hits[pos][1];
            
            if (grid[i][j] == 0)
                hits[pos] = null;
            else
                grid[i][j] = 0;
        }
    }
    
    private static DisjointCoordinateSets ConstructSets(int[][] grid)
    {
        var sets = new DisjointCoordinateSets(grid.Length, grid[0].Length);
        
        for (var j = 0; j != sets.Width; ++j)
            if (grid[0][j] != 0) sets.ConnectToRoot(0, j);
        
        for (var i = 0; i != sets.Height; ++i) {
            for (var j = 0; j != sets.Width; ++j) {
                if (grid[i][j] == 0) continue;
                
                TryConnect(grid, sets, i, j, i + 1, j);
                TryConnect(grid, sets, i, j, i, j + 1);
            }
        }
        
        return sets;
    }
    
    private static void Add(int[][] grid, DisjointCoordinateSets sets,
                            int i, int j)
    {
        Contract.Assert(grid[i][j] == 0);
        grid[i][j] = 1;
        
        if (i == 0) sets.ConnectToRoot(i, j);
        
        TryConnect(grid, sets, i, j, i - 1, j);
        TryConnect(grid, sets, i, j, i + 1, j);
        TryConnect(grid, sets, i, j, i, j - 1);
        TryConnect(grid, sets, i, j, i, j + 1);
    }
    
    private static void TryConnect(int[][] grid, DisjointCoordinateSets sets,
                                   int i, int j, int ii, int jj)
    {
        if (0 <= ii && ii < sets.Height && 0 <= jj && jj < sets.Width
                                        && grid[ii][jj] != 0)
            sets.Connect(i, j, ii, jj);
    }
}

internal static class UnitTest {
    private static void Main()
    {
        var s = new Solution();
        
        var grid1 = new[] { new[] { 1, 0, 0, 0 },
                            new[] { 1, 1, 1, 0 } };

        var hits1 = new[] { new[] { 1, 0 } };
        
        s.HitBricks(grid1, hits1).Dump("1");
        
        var grid2 = new[] { new[] { 1, 0, 0, 0 },
                            new[] { 1, 1, 0, 0 } };

        var hits2 = new[] { new[] { 1, 1 }, new[] { 1, 0 } };
        
        s.HitBricks(grid2, hits2).Dump("2");
    }
}
