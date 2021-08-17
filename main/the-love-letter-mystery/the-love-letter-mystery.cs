using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var s = Console.ReadLine();
            var n = s.Length - 1;

            Console.WriteLine(Enumerable.Range(0, s.Length / 2)
                                        .Sum(i => Math.Abs(s[i] - s[n - i])));
        }
    }
}
