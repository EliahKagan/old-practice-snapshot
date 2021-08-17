using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        // Takes a number n as input and outputs the value of n!.
        Console.WriteLine(Enumerable.Range(1, int.Parse(Console.ReadLine()))
                                    .Aggregate(1, (m, n) => checked(m * n)));
    }
}
