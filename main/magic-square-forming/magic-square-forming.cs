using System;

internal static class Solution {
    private static void Main()
    {
        // All eight 3x3 magic squares. See:
        // https://mindyourdecisions.com/blog/2015/11/08/how-many-3x3-magic-squares-are-there-sunday-puzzle/
        var squares = new[] {
            new[] { 8, 1, 6, 3, 5, 7, 4, 9, 2 },
            new[] { 6, 1, 8, 7, 5, 3, 2, 9, 4 },
            new[] { 4, 9, 2, 3, 5, 7, 8, 1, 6 },
            new[] { 2, 9, 4, 7, 5, 3, 6, 1, 8 },
            new[] { 8, 3, 4, 1, 5, 9, 6, 7, 2 },
            new[] { 4, 3, 8, 9, 5, 1, 2, 7, 6 },
            new[] { 6, 7, 2, 1, 5, 9, 8, 3, 4 },
            new[] { 2, 7, 6, 9, 5, 1, 4, 3, 8 }
        };
        
        var a = Array.ConvertAll(System.Console.In.ReadToEnd().Split(),
                                 int.Parse);
        
        var best = int.MaxValue;
        
        foreach (var s in squares) {
            var cur = 0;
            for (var i = 0; i != s.Length; ++i) cur += Math.Abs(a[i] - s[i]);
            if (best > cur) best = cur;
        }
        
        Console.WriteLine(best);
    }
}
