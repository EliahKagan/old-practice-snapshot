using System;
using System.Linq;

internal static class Solution {
    private static void GetState(out int n, out int m, out int s)
    {
        var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

        n = a[0];
        m = a[1];
        s = a[2];
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            int n, m, s;
            GetState(out n, out m, out s);
            Console.WriteLine((s + m - 2) % n + 1);
        }
    }
}
