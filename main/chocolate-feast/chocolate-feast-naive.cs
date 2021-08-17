// naive solution to "Chocolate Feast" - for reference only
// not intended for submission (would be far too slow for given constraints)

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
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            int n, c, m;
            using (var en = GetRecord(3).GetEnumerator()) {
                en.MoveNext();    n = en.Current;
                en.MoveNext();    c = en.Current;
                en.MoveNext();    m = en.Current;
            }

            var choc = n / c;
            for (var wrap = choc; (wrap -= m) >= 0; ++wrap) ++choc;
            Console.WriteLine(choc);
        }
    }
}