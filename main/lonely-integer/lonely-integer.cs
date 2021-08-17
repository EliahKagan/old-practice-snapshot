using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());

        Console.WriteLine(Console.ReadLine().Split(' ')
                                            .Select(int.Parse)
                                            .Take(n)
                                            .Aggregate((i, j) => i ^ j));
    }
}
