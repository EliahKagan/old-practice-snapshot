<Query Kind="Program">
  <Namespace>static System.Console</Namespace>
</Query>

internal static class Solution {
    private static IEnumerable<int> ComputePathSums(this int[][] grid)
    {
        foreach (var bits in Enumerable.Range(0, 1 << grid.Length)) {
            var acc = grid[0][0];
            
            var mask = bits;
            var j = 0;
            
            for (var i = 1; i != grid.Length; acc += grid[i++][j], mask >>= 1)
                if ((mask & 1) != 0) ++j;
            
            yield return acc;
        }
    }
    
    private static int Get() => int.Parse(ReadLine());
    
    private static int[][] ReadGrid()
    {
        var grid = new int[Get()][];
        
        for (var i = 0; i != grid.Length; ++i)
            grid[i] = ReadLine().Split(' ').Select(int.Parse).ToArray();
        
        return grid;
    }
    
    private static void Main()
    {
        for (var t = Get(); t > 0; --t)
            WriteLine(ReadGrid().ComputePathSums().Max());
    }
}