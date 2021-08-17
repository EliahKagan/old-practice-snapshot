using System;
using System.Linq;

internal static class Solution {
    private static int SquaresBetween(int first, int last)
    {
        var m = (int)Math.Sqrt(first);
        if (m * m < first) ++m;

        var n = (int)Math.Sqrt(last);
        if (n * n > last) --n;

        return m <= n ? n - m + 1 : 0;
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var range = Console.ReadLine().Split(' ')
                                          .Select(int.Parse)
                                          .Take(2);

            Console.WriteLine(SquaresBetween(range.First(), range.Last()));
        }
    }
}
