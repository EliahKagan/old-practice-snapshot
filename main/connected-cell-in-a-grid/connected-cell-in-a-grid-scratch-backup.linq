<Query Kind="Program" />

private static IEnumerable<int> ConnectedAreas(int[][] a, int m, int n)
{
    var imax = m - 1;
    var jmax = n - 1;
    
    var s = Array.ConvertAll(a, row => row.Sum());
    for (var k = 0; (k = Array.FindIndex(s, k, sum => sum != 0)) != -1; ) {
        var area = 0;
        
        var q = new Queue<Tuple<int, int>>();
        Action<int, int> enq = (i, j) => q.Enqueue(Tuple.Create(i, j));
        enq(k, Array.IndexOf(a[k], 1));
        
        do {
            var ij = q.Dequeue();
            var i = ij.Item1;
            var j = ij.Item2;
            
            ++area;
            --s[i];
            a[i][j] = 0;
            
            if (i != 0 && a[i - 1][j] == 1) enq(i - 1, j);
            if (i != imax && a[i + 1][j] == 1) enq(i + 1, j);
            if (j != 0 && a[i][j - 1] == 1) enq(i, j - 1);
            if (j != jmax && a[i][j + 1] == 1) enq(i, j + 1);
        }
        while (q.Count != 0);
        
        yield return area;
    }
}

private static int MaxConnectedArea(int[][] a, int m, int n)
        => ConnectedAreas(a, m, n).DefaultIfEmpty().Max();

private static void Main()
{
    var a = new[] {new[] {1,0,0,0}, new[] {1,1,0,0}, new[] {0,0,1,1}};
    ConnectedAreas(a, 3, 4).DefaultIfEmpty().Max().Dump();
    
    var b = new[] {new[] {0,0}, new[] {0,0}};
    ConnectedAreas(b, 2, 2).DefaultIfEmpty().Max().Dump();
    
    var c = new[] {new[] {1,1,1,1},
                   new[] {0,0,1,0},
                   new[] {0,1,1,1},
                   new[] {1,1,0,0}, // 10
                   new[] {0,0,1,1},
                   new[] {1,1,1,1},
                   new[] {0,1,1,0},
                   new[] {0,1,0,1}, // 9
                   new[] {1,0,1,1},
                   new[] {1,1,1,1}}; // 7
    MaxConnectedArea(c, 10, 4).Dump();
}
