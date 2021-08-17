using System;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    private static void Main()
    {
        var regex = new Regex(@"^[A-Z]{5}\d{4}[A-Z]$");

        foreach (var i in Enumerable.Range(0, int.Parse(Console.ReadLine())))
            Console.WriteLine(regex.IsMatch(Console.ReadLine()) ? "YES" : "NO");
    }
}
