using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());

        foreach (var i in Enumerable.Range(1, n))
            Console.WriteLine(new string('#', i).PadLeft(n));
    }
}
