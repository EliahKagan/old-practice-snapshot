#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Globalization;
using System.Linq;

internal static class Solution {
    private static IEnumerable<int> Range(int n)
    {
        return Enumerable.Range(0, n);
    }

    private static void Main()
    {
        foreach (var t in Range(int.Parse(Console.ReadLine()))) {
            var s = Console.ReadLine().Trim();
            var n = int.Parse(s, CultureInfo.InvariantCulture);
            Contract.Assert(n >= 0); // problem constraint is actually stronger

            Console.WriteLine(Range(s.Length)
                                .Select(i => int.Parse(s.Substring(i, 1)))
                                .Count(k => k != 0 && n % k == 0));
        }
    }
}
