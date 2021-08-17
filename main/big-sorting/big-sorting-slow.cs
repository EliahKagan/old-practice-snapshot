using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());

        var sorted = from _ in Enumerable.Range(0, n)
                     select Console.ReadLine().Trim() into s
                     orderby s.Length, s
                     select s;

        foreach (var s in sorted) Console.WriteLine(s);
    }
}
