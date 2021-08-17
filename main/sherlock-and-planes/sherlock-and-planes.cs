using System;
using System.Collections.Generic;
using System.Linq;

internal static class Algebra {
    private static int Det2(int a, int b,
                            int c, int d)
    {
        return a * d - b * c;
    }

    internal static int Det3(int a, int b, int c,
                             int d, int e, int f,
                             int g, int h, int i)
    {
        return a * Det2(e, f,
                        h, i) - b * Det2(d, f,
                                         g, i) + c * Det2(d, e,
                                                          g, h);
    }
}

internal static class Solution {
    private static IEnumerable<int> Range(int count)
    {
        return Enumerable.Range(0, count);
    }

    private static readonly IEnumerable<int> Quad = Range(4);

    private static int[] GetRow()
    {
        return Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
    }

    private static void Run()
    {
        var m = Quad.Select(k => GetRow()).ToArray();

        var det = Algebra.Det3(
                    m[1][0] - m[0][0], m[1][1] - m[0][1], m[1][2] - m[0][2],
                    m[2][0] - m[0][0], m[2][1] - m[0][1], m[2][2] - m[0][2],
                    m[3][0] - m[0][0], m[3][1] - m[0][1], m[3][2] - m[0][2]);

        Console.WriteLine(det == 0 ? "YES" : "NO");
    }

    private static void Main()
    {
        foreach (var t in Range(int.Parse(Console.ReadLine()))) Run();
    }
}
