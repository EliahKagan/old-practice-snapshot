using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static int GetNumber() => int.Parse(Console.ReadLine());

    private static IEnumerable<int> PossibleFinalValues(int n, int a, int b)
    {
        if (n <= 1) return Enumerable.Repeat(0, 1);

        var hops = n - 1;
        return Enumerable.Range(0, n).Select(i => a * i + b * (hops - i))
                                     .OrderBy(k => k)
                                     .Distinct();
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, GetNumber())) {
            var n = GetNumber();
            var a = GetNumber();
            var b = GetNumber();

            Console.WriteLine(string.Join(" ", PossibleFinalValues(n, a, b)));
        }
    }
}
