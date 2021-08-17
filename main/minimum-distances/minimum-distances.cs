using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static IEnumerable<IGrouping<int, int>> EqualIndices(this int[] a)
            => Enumerable.Range(0, a.Length).GroupBy(i => a[i]);

    private static IEnumerable<int> Deltas(this IEnumerable<int> values)
    {
        var v = values.ToArray();
        Array.Sort(v);
        return Enumerable.Range(0, v.Length - 1).Select(i => v[i + 1] - v[i]);
    }

    private static int MinEqualIndexDelta(this int[] a)
            => a.EqualIndices().SelectMany(Deltas).DefaultIfEmpty(-1).Min();

    private static int[] GetRecord()
            => Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

    private static void Main()
    {
        Console.ReadLine(); // don't need n
        Console.WriteLine(GetRecord().MinEqualIndexDelta());
    }
}
