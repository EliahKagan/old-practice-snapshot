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
            var n_k = GetRecord(2);
            var n = n_k.First();
            var k = n_k.Last();

            var s = (GetRecord(n).Count(time => time <= 0) < k ? "YES" : "NO");
            Console.WriteLine(s);
        }
    }
}
