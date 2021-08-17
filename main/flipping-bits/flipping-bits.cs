using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine())))
            Console.WriteLine(~uint.Parse(Console.ReadLine()));
    }
}
