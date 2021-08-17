using System;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    private static void Main()
    {
        // will tokenize into words (slow, but simple, and N and W are small)
        var regex = new Regex(@"\w+");

        foreach (var i in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var matches = regex.Matches(Console.ReadLine());

            if (matches.Count == 0) {
                Console.WriteLine(-1);
                continue;
            }

            var tokens = matches.Cast<Match>();

            if (tokens.First().Value == "hackerrank")
                Console.WriteLine(tokens.Last().Value == "hackerrank" ? 0 : 1);
            else if (tokens.Last().Value == "hackerrank")
                Console.WriteLine(2);
            else
                Console.WriteLine(-1);

        }
    }
}
