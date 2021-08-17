using System;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

[assembly: System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Solution {
    // This program matches text that looks like it is a web link containing
    // a possibly valid Internet domain name, without checking the surrounding
    // context to ensure it (i.e., the <a> tag with href attribute) isn't
    // quoted. This risks false positives, but I think that's better than the
    // false negatives that would arise from HTML employing unanticipated
    // constructs (or that is malformed). Regexes really aren't good for HTML.
    private static readonly Regex LinkTagRegex;

    static Solution()
    {
        // web URL, up to the end of the domain name
        const string protocol = @"https?(:|%3A)(/|%2F){2}";
        const string www = @"www?\d*\.";
        const string prefix = @"(" + www + @")?" + @"(?!" + www + @")";
        const string domain = @"(?<domain>[\w-]+(\.[\w-]+)+)(?![\w-.])";
        const string urlroot = protocol + prefix + domain;

        // href attribute, with quoted URL as value
        const string urlvalue_dq = @"(""" + urlroot + @"[^""]*"")";
        const string urlvalue_sq = @"('" + urlroot + @"[^']*')";
        const string urlvalue = @"(" + urlvalue_dq + @"|" + urlvalue_sq + @")";
        const string href = @"\s+href=" + urlvalue;

        // other attributes
        const string value = @"((""[^""]*"")|('[^']*'))"; // dq | sq
        const string attrs = @"(\s+(?!href=)[a-z][a-z\d]*(=" + value + @")?)*";

        // regex to attempt to match hyperlinks and scrape their domains
        const string pattern = @"(?in)<a" + attrs + href + attrs + @"\s*>";
        LinkTagRegex = new Regex(pattern, RegexOptions.Compiled);
    }

    private static string ReadToEnd()
    {
        using (var sr = new StreamReader(Console.OpenStandardInput()))
            return sr.ReadToEnd();
    }

    private static void Main()
    {
        var domains = LinkTagRegex.Matches(ReadToEnd())
                                    .Cast<Match>()
                                    .Select(m => m.Groups["domain"].Value)
                                    .OrderBy(s => s, StringComparer.Ordinal)
                                    .Distinct(StringComparer.Ordinal);

        Console.WriteLine(string.Join(";", domains));
    }
}
