using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var s = Console.ReadLine().Split(' ').Select(int.Parse).Take(n).Sum();
        Console.WriteLine(s);
    }
}
