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
        var match_word = new Regex(@"^\w+$");

        var text = string.Join(" ", GetLines());

        var counts = from r in GetLines()
                     select match_word.IsMatch(r)
                      ? Regex.Matches(text, string.Format(@"\w{0}\w", r)).Count
                      : 0;

        foreach (var count in counts) Console.WriteLine(count);
    }
}
