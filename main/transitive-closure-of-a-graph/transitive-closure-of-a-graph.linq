<Query Kind="Program">
  <Namespace>System.Diagnostics.Contracts</Namespace>
</Query>

internal static class Solution {
    private static void Main()
    {
        for (var t = ReadValue(); t > 0; --t) {
            var a = ReadAdjacencyMatrix();
            var n = a.GetLength(0);
            
            if (n == 1)
                Console.WriteLine("1");
            else
                a.Pow(n - 1).Display();
        }
    }

    private static bool[,] ReadAdjacencyMatrix()
    {
        var a = ReadMatrix();
        var n = a.GetLength(0);
        for (var h = 0; h != n; ++h) a[h, h] = true;
        return a;
    }
    
    private static bool[,] ReadMatrix()
    { 
        var n = ReadValue();
        var a = new bool[n, n];
        
        using (var en = ReadTokens().Select(s => s == "1").GetEnumerator()) {
            for (var i = 0; i != n; ++i) {
                for (var j = 0; j != n; ++j) {
                    en.MoveNext();
                    a[i, j] = en.Current;
                }
            }
        }
        
        return a;
    }
    
    private static int ReadValue() => int.Parse(Console.ReadLine());
    
    private static string[] ReadTokens()
        => Console.ReadLine().Split((char[])null,
                                    StringSplitOptions.RemoveEmptyEntries);
    
    /// <summary>Multiplies square boolean matrices.</summary>
    private static bool[,] Mul(this bool[,] a, bool[,] b)
    {
        var n = a.GetLength(0);
        var c = new bool[n, n];
        
        for (var i = 0; i != n; ++i) {
            for (var j = 0; j != n; ++j)
                c[i, j] = a.Row(i).Dot(b.Col(j));
        }
        
        return c;
    }
    
    /// <summary>Takes the boolean inner product of a row and column.</summary>
    private static bool Dot(this IEnumerable<bool> row, IEnumerable<bool> col)
        => row.Zip(col, (rowElem, colElem) => rowElem && colElem).Any(x => x);
    
    private static IEnumerable<bool> Row(this bool[,] a, int i)
    {
        var n = a.GetLength(0);
        for (var j = 0; j != n; ++j) yield return a[i, j];
    }
    
    private static IEnumerable<bool> Col(this bool[,] a, int j)
    {
        var n = a.GetLength(0);
        for (var i = 0; i != n; ++i) yield return a[i, j];
    }
    
    /// <summary>Raises a square boolean matrix to a positive power.</summary>
    private static bool[,] Pow(this bool[,] a, int p)
    {
        if (p == 1) return a;
        
        var r = a.Pow(p / 2);
        var s = r.Mul(r);
        return p % 2 == 0 ? s : s.Mul(a);
    }
    
    private static void Display(this bool[,] a)
    {
        var n = a.GetLength(0);
        var sb = new StringBuilder();
        
        for (var i = 0; i != n; ++i) {
            for (var j = 0; j != n; ++j)
                sb.Append(a[i, j] ? "1 " : "0 ");
        }
        
        sb.Remove(sb.Length - 1, 1);
        Console.WriteLine(sb);
    }
}