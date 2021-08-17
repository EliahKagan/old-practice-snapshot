using System;
using System.IO;
using System.Text.RegularExpressions;

internal static class Solution {
    private static readonly Regex ScrapeRegex;

    static Solution()
    {
        const string link = @"<h3>\s*<a\s+href=""/questions/(?<id>\d+)/"
                          + @"[^\s/""]+""\s+class=""question-hyperlink""\s*>"
                          + @"(?<title>[^<>]+)</a>\s*</h3>";

        const string not_time = @"(?:(?!<div\s+class=""user-action-time"").)*";

        const string time = @"<div\s+class=""user-action-time""\s*>\s*asked\s*"
                          + @"<span\s+title=""[^""]+""\s+class=""[^""]+""\s*>"
                          + @"(?<time>[^<>]+)</span>\s*</div>";

        const string pattern = "(?is)" + link + not_time + time;
        ScrapeRegex = new Regex(pattern, RegexOptions.Compiled);
    }

    private static string ReadToEnd()
    {
        using (var sr = new StreamReader(Console.OpenStandardInput()))
            return sr.ReadToEnd();
    }

    private static string[] SplitWords(string s) => s.Split((char[])null);

    private static string ReduceWhitespace(this string s)
            => string.Join(" ", SplitWords(s));

    private static void Main()
    {
        foreach (Match m in ScrapeRegex.Matches(ReadToEnd())) {
            Console.WriteLine("{0};{1};{2}", m.Groups["id"].Value,
                              m.Groups["title"].Value.ReduceWhitespace(),
                              m.Groups["time"].Value.ReduceWhitespace());
        }
    }
}
