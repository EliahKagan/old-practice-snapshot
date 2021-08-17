using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var range = Console.ReadLine().Split(' ')
                                          .Select(int.Parse)
                                          .Take(2);
            var first = range.First();
            var last = range.Last();

            Func<int, int> sq = k => k * k;
            var n = Enumerable.Range(first, last - first + 1)
                              .Count(i => sq((int)Math.Sqrt(i)) == i);

            Console.WriteLine(n);
        }
    }
}
