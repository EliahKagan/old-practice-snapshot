<Query Kind="Program" />

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
    private static bool // assumes (i1, i2) != (j1, j2)
    AreDisjoint(int i1, int j1, int b1, int i2, int j2, int b2)
    {
        var di = Math.Abs(i1 - i2);
        var dj = Math.Abs(j1 - j2);

        var bsum = b1 + b2;
        if (di == 0) return dj > bsum;
        if (dj == 0) return di > bsum;

        return Math.Max(di, dj) > Math.Max(b1, b2);
    }

    private static int Area(int branch) => branch * 4 + 1;

    private static IEnumerable<int>
    DisjointSubcrossAreaProducts(this Cross x, Cross y)
    {
        for (var bx = x.Branch; bx >= 0; --bx) {
            for (var by = y.Branch; by >= 0; --by) {
                if (AreDisjoint(x.Row, x.Col, bx, y.Row, y.Col, by)) {
                    var p = Area(bx) * Area(by);
                    //if (p == 117) Console.Error.WriteLine($"x.Row={x.Row}, x.Col={x.Col}, bx={bx}, y.Row={y.Row}, y.Col={y.Col}, by={by}");
                    yield return p;
                    //yield return Area(bx) * Area(by);
                }
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
        var n = 10;
        var m = 10;
        
        return new string[] { "BBBBBGGBGG",
                              "GGGGGGGGGG",
                              "GGGGGGGGGG",
                              "BBBBBGGBGG",
                              "BBBBBGGBGG",
                              "GGGGGGGGGG",
                              "BBBBBGGBGG",
                              "GGGGGGGGGG",
                              "BBBBBGGBGG",
                              "GGGGGGGGGG" }.GetFullCrosses(n, m);
    
        //int n, m;
        //return ReadGrid(out n, out m).GetFullCrosses(n, m);
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
    {
        
        Console.WriteLine(Grid.ReadFullCrosses().Dump()
                              .MaxDisjointCrossAreaProduct());
    }

    //private static void Main()
    //    => Console.WriteLine(Grid.ReadFullCrosses()
    //                             .MaxDisjointCrossAreaProduct());
}
