using System;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    private static void Main()
    {
        var regex = new Regex(@"^[a-z]{0,3}\d{2,8}[A-Z]{3,}$");

        foreach (var i in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            Console.WriteLine(regex.IsMatch(Console.ReadLine()) ? "VALID"
                                                                : "INVALID");
        }
    }
}
