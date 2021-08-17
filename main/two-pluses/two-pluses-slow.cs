using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("0.1.0.1")]

internal struct Cross {
    public readonly int Row, Col, Branch;
    
    public Cross(int row, int col, int branch)
    {
        Row = row;
        Col = col;
        Branch = branch;
    }
}

internal static class CrossEx {
    private static bool AreDisjoint(int i1, int j1, int b1,
                                    int i2, int j2, int b2)
    {
        var di = Math.Abs(i1 - i2);
        var dj = Math.Abs(j1 - j2);
        
        if (di == 0) return dj > b1 + b2;
        if (dj == 0) return di > b1 + b2;

        return (di > b1 || dj > b2) && (di > b2 || dj > b1);
    }

    private static int Area(int branch) => branch * 4 + 1;

    private static IEnumerable<int>
    DisjointSubcrossAreaProducts(this Cross x, Cross y)
    {
        for (var bx = x.Branch; bx >= 0; --bx) {
            for (var by = y.Branch; by >= 0; --by) {
                if (AreDisjoint(x.Row, x.Col, bx, y.Row, y.Col, by))
                    yield return Area(bx) * Area(by);
            }
        }
    }

    internal static int MaxDisjointSubcrossAreaProduct(this Cross x, Cross y)
        => x.DisjointSubcrossAreaProducts(y).DefaultIfEmpty().Max();
}

internal static class Grid {
    private static void ReadDoublet(out int first, out int second)
    {
        var tok = Console.ReadLine().Split();
        
        first = int.Parse(tok[0]);
        second = int.Parse(tok[1]);
    }

    private static string[] ReadGrid(out int n, out int m)
    {
        ReadDoublet(out n, out m); // n rows, m cols
        
        return Enumerable.Range(0, n)
                         .Select(i => Console.ReadLine().Trim())
                         .ToArray();
    }
    
    private static bool Ok(this string[] grid, int i, int j) 
        => grid[i][j] == 'G';
    
    private static int GetBranch(this string[] grid,
                                 int n, int m, int i, int j)
    {
        var d = Math.Min(Math.Min(i, n - i - 1), Math.Min(j, m - j - 1));
        var b = 1;

        while (b <= d && grid.Ok(i, j - b) && grid.Ok(i, j + b)
                      && grid.Ok(i - b, j) && grid.Ok(i + b, j)) ++b;
        
        return b - 1;
    }

    private static IEnumerable<Cross> GetFullCrosses(this string[] grid,
                                                     int n, int m)
    {
        for (var i = 0; i != n; ++i) {
            for (var j = 0; j != m; ++j) {
                if (grid.Ok(i, j))
                    yield return new Cross(i, j, grid.GetBranch(n, m, i, j));
            }
        }
    }
    
    internal static IEnumerable<Cross> ReadFullCrosses()
    {
        int n, m;
        return ReadGrid(out n, out m).GetFullCrosses(n, m);
    }
}

internal static class Solution {
    private static int
    MaxDisjointCrossAreaProduct(this IEnumerable<Cross> fullCrosses)
    {
        var c = fullCrosses.ToArray();
        var p = 0;
        
        var istop = c.Length - 1;
        for (var i = 0; i < istop; ++i) {
            for (var j = i + 1; j != c.Length; ++j)
                p = Math.Max(p, c[i].MaxDisjointSubcrossAreaProduct(c[j]));
        }
        
        return p;
    }

    private static void Main()
        => Console.WriteLine(Grid.ReadFullCrosses()
                                 .MaxDisjointCrossAreaProduct());
}
