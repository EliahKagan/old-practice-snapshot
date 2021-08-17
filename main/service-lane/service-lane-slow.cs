using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static IEnumerable<int> GetRecord(int fields)
    {
        return Console.ReadLine().Split().Select(int.Parse).Take(fields);
    }

    private static void Main()
    {
        var n_t = GetRecord(2);
        var n = n_t.First();
        var t = n_t.Last();

        var widths = GetRecord(n);

        foreach (var testcase in Enumerable.Range(0, t)) {
            var i_j = GetRecord(2);
            var i = i_j.First();
            var j = i_j.Last();

            Console.WriteLine(widths.Skip(i).Take(j - i + 1).Min());
        }
    }
}
