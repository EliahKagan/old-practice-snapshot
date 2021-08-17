#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    private static void Main()
    {
        var regex = new Regex(@"^\s*(?<CountryCode>\d{1,3})[- ]"
                            + @"(?<LocalAreaCode>\d{1,3})[- ]"
                            + @"(?<Number>\d{4,10})\s*$");

        foreach (var i in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var match = regex.Match(Console.ReadLine());
            Contract.Assert(match.Success && match.Groups.Count == 4);

            var pairs = regex.GetGroupNames().Skip(1).Select(
                            s => string.Format("{0}={1}", s, match.Groups[s]));

            Console.WriteLine(string.Join(",", pairs));
        }
    }
}
