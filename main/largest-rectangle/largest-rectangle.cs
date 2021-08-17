using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static readonly IEnumerable<long> Zero = Enumerable.Repeat(0L, 1);

    private static long ComputeMaxArea(this IEnumerable<long> heights)
    {
        var h = Zero.Concat(heights).Concat(Zero).ToArray();
        var lefts = new Stack<int>(h.Length);
        var acc = 0L;

        foreach (var right in Enumerable.Range(0, h.Length)) {
            while (lefts.Count != 0 && h[lefts.Peek()] > h[right]) {
                var left = lefts.Pop();

                var width = right;
                if (lefts.Count != 0) width -= 1 + lefts.Peek();

                acc = Math.Max(acc, h[left] * width);
            }

            lefts.Push(right);
        }

        return acc;
    }

    private static void Main()
    {
        Console.ReadLine(); // don't need n

        Console.WriteLine(Console.ReadLine().Split().Select(long.Parse)
                                                    .ComputeMaxArea());
    }
}
