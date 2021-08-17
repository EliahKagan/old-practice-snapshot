using System;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    private static void Main()
    {
        var regex = new Regex("hackerrank", RegexOptions.IgnoreCase);

        var count = Enumerable.Range(0, int.Parse(Console.ReadLine()))
                              .Count(i => regex.IsMatch(Console.ReadLine()));

        Console.WriteLine(count);
    }
}
