using System;

internal static class Solution {
    private static void Main()
    {
        var s = Console.ReadLine().Replace(" ", string.Empty);
        var n = s.Length;
        var sqrt = Math.Sqrt(n);
        var h = Convert.ToInt32(Math.Floor(sqrt));
        var w = Convert.ToInt32(Math.Ceiling(sqrt));
        if (h * w < n) ++h;

        var grid = new char[w][]; // column-major ciphertext representation
        var newcol = new string(' ', h);
        for (var j = 0; j < w; ++j)
            grid[j] = newcol.ToCharArray();

        for (var k = 0; k < n; ++k)
            grid[k % w][k / w] = s[k];

        var words = Array.ConvertAll(grid, col => new string(col).TrimEnd());
        Console.WriteLine(string.Join(" ", words));
    }
}
