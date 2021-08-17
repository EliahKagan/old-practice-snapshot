using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    private static IEnumerable<string> GetLines()
    {
        return from i in Enumerable.Range(0, int.Parse(Console.ReadLine()))
               select Console.ReadLine();
    }

    private static void Main()
    {
        var filter = new Regex(@"^(\w+o)u(r\w*)$");
        var text = string.Join(" ", GetLines());

        foreach (var word in GetLines()) {
            var filter_match = filter.Match(word);

            if (!filter_match.Success || filter_match.Groups.Count != 3) {
                Console.WriteLine(0);
                continue;
            }

            var groups = filter_match.Groups.Cast<Group>().Skip(1);
            var pattern = string.Format(@"\b{0}u?{1}\b", groups.First().Value,
                                                         groups.Last().Value);

            Console.WriteLine(Regex.Matches(text, pattern).Count);
        }
    }
}
