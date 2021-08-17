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
        // Going by the problem statement, all words ending in -se are taken as
        // the UK variants of the same word with -ze instead -- even if the
        // "se" and "ze" are not preceded by an "i".
        var filter = new Regex(@"^\w+(?=ze$)");

        var text = string.Join(" ", GetLines());

        foreach (var word in GetLines()) {
            var filter_match = filter.Match(word);

            var m = filter_match.Success
                    ? Regex.Matches(text,
                                    string.Format(@"\b{0}[sz]e\b",
                                                  filter_match.Value)).Count
                    : 0;

            Console.WriteLine(m);
        }
    }
}
