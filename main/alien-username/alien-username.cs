using System;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    private static void Main()
    {
        var regex = new Regex(@"^[_.]\d+[A-Za-z]*_?$");

        foreach (var n in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            Console.WriteLine(regex.IsMatch(Console.ReadLine()) ? "VALID"
                                                                : "INVALID");
        }
    }
}
