<Query Kind="Program" />

internal struct Pair {
    public readonly int X, Y;
    
    public Pair(int x, int y)
    {
        X = x;
        Y = y;
    }
}

internal struct Cross {
    public readonly int Row, Col, Branch;
    
    public Cross(int row, int col, int branch)
    {
        Row = row;
        Col = col;
        Branch = branch;
    }
}

internal static class Test {
    private static void GetMinMax(int lhs, int rhs,
                                  out int min, out int max)
    {
        if (lhs < rhs) {
            min = lhs;
            max = rhs;
        } else {
            min = rhs;
            max = lhs;
        }
    }
    
    private static Pair GetBestBranchesFromSum(int bx, int by, int bsum)
    {
        if (bx + by <= bsum) return new Pair(bx, by);
        
        var bhalf_low = bsum / 2;
        var bhalf_high = bhalf_low + bsum % 2;
        
        int small, big; // OK: in our use case, the order can be switched
        GetMinMax(bx, by, out small, out big);
        
        return small > bhalf_high
                ? new Pair(bhalf_high, bhalf_low)
                : new Pair(small, bsum - small); // OK: big > bsum - small
    }
    
    private static Pair GetBestBranchesFromMax(int bx, int by, int bmax)
        => new Pair(Math.Min(bx, bmax), Math.Min(by, bmax));
    
    private static Pair GetBestBranches(Cross x, Cross y)
    {
        var di = Math.Abs(x.Row - y.Row);
        var dj = Math.Abs(x.Col - y.Col);
        
        var bx = x.Branch;
        var by = y.Branch;
        
        if (di == 0) return GetBestBranchesFromSum(bx, by, dj - 1);
        if (dj == 0) return GetBestBranchesFromSum(bx, by, di - 1);
        
        new { di, dj, bx, by }.Dump();
        
        return GetBestBranchesFromMax(bx, by, Math.Min(di, dj) - 1);
    }
    
    private static void Main()
    {
        GetBestBranches(new Cross(3, 3, 3), new Cross(6, 2, 2)).Dump();
    }
}