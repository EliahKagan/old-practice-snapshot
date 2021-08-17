using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        IEnumerable<char> common = "abcdefghijklmnopqrstuvwxyz";
        foreach (var n in Enumerable.Range(0, int.Parse(Console.ReadLine())))
            common = Console.ReadLine().Intersect(common);

        Console.WriteLine(common.Count());
    }
}
