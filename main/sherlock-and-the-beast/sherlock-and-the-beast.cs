using System;
using System.Linq;

internal static class Solution {
    private static int Get()
    {
        return int.Parse(Console.ReadLine());
    }

    private static string MaxDecent(int n)
    {
        for (var fives = n; fives >= 0; --fives) {
            var threes = n - fives;
            if (fives % 3 == 0 && threes % 5 == 0)
                return new string('5', fives).PadRight(n, '3');
        }

        return "-1";
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, Get()))
            Console.WriteLine(MaxDecent(Get()));
    }
}
