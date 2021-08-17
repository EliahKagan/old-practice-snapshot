<Query Kind="Program" />

internal static class Test {
    private static bool Ok(this string[] grid, int i, int j)
    {
        new { i, j, ok = grid[i][j] == 'G' }.Dump();
        return grid[i][j] == 'G';
    }
    
    private static int GetBranch(this string[] grid,
                                 int n, int m, int i, int j)
    {
        var d = Math.Min(Math.Min(i, n - i - 1), Math.Min(j, m - j - 1));
        var b = 1;
        
        new { i, j }.Dump();
        while (b <= d && grid.Ok(i + b, j + b) && grid.Ok(i + b, j - b)
                      && grid.Ok(i - b, j + b) && grid.Ok(i - b, j - b)) ++b;
        
        return b - 1;
    }
    
    private static void Main()
    {
        var n = 5;
        var m = 6;
        var grid = new[] { "GGGGGG", "GBBBGB", "GGGGGG", "GGBBGB", "GGGGGG" };
        
        grid.GetBranch(n, m, 1, 4).Dump();
    }
}