#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Program {
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        Contract.Assert(1 <= n && n <= 20);

        var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Contract.Assert(a.Length == n);

        Array.Sort(a);
        var b = a.Distinct().ToArray();
        var bij = (b.Length == n && b[0] == 1 && b[n - 1] == n);

        Console.WriteLine(bij ? "YES" : "NO");
    }
}
