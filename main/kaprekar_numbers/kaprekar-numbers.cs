using System;
using System.Collections.Generic;

internal static class Solution {
    private static IEnumerable<long> ModifiedKaprekar(long p, long q)
    {
        if (p < 9) {
            if (p == 1) yield return 1;
            p = 9;
        }

        for (; p <= q; ++p) {
            var s = (p * p).ToString();
            var wl = s.Length / 2;
            var left = long.Parse(s.Substring(0, wl));
            var right = long.Parse(s.Substring(wl));
            if (left + right == p) yield return p;
        }
    }

    private static long GetNumber() => long.Parse(Console.ReadLine());

    private static void Main()
    {
        var s = string.Join(" ", ModifiedKaprekar(GetNumber(), GetNumber()));
        Console.WriteLine(s.Length == 0 ? "INVALID RANGE" : s);
    }
}
