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

        var texts = GetLines().ToArray();
        
        foreach (var s in GetLines()) {
            if (!match_word.IsMatch(s)) {
                Console.WriteLine(0);
                continue;
            }

            var r = new Regex(string.Format(@"\b{0}\b", s));
            Console.WriteLine(texts.Sum(t => r.Matches(t).Count));
        }
    }
}
