#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var s = Console.ReadLine();
            var r = new string(s.Reverse().ToArray());

            Contract.Assert(s.Length > 0);
            var funny = Enumerable.Range(1, s.Length - 1)
                                  .All(j => Math.Abs(s[j] - s[j - 1])
                                         == Math.Abs(r[j] - r[j - 1]));

            Console.WriteLine(funny ? "Funny" : "Not Funny");
        }
    }
}
