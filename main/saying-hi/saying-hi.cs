using System;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    private static void Main()
    {
        var regex = new Regex(@"^hi (?!d)", RegexOptions.IgnoreCase);

        foreach (var i in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var line = Console.ReadLine();
            if (regex.IsMatch(line)) Console.WriteLine(line);
        }
    }
}
