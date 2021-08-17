using System;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

[assembly: System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Solution {
    private static readonly Regex HyperlinkRegex;

    static Solution()
    {
        // parts appearing in HTML attributes or tags
        const string word = @"[a-z][a-z\d]*";
        const string non_a_word = @"(?!a[^a-z\d])" + word;
        const string link = @"(?:""(?<url>[^""]+)""|'(?<url>[^']+)')";

        // single HTML attributes
        const string attr_trim = word + @"=(?:""[^""]*""|'[^']*')";
        const string attr = @"\s+" + attr_trim;
        const string href = @"\s+href=" + link;
        const string non_href = @"\s+(?!href=)" + attr_trim;

        // quantified (i.e., possibly multiple) HTML attributes
        const string multi_attr = @"(?:" + attr + @")*";
        const string multi_non_href = @"(?:" + non_href + @")*";
        const string a_attrs = multi_non_href + href + multi_non_href;

        // HTML tags
        const string a = @"<a" + a_attrs + @"\s*>";
        const string a_end = @"</a>";
        const string non_a = @"<" + non_a_word + multi_attr + @"\s*/?\s*>";
        const string non_a_end = @"</" + non_a_word + @"\s*>";
        const string non_a_any = @"(?:" + non_a + @"|" + non_a_end + @")";

        // various hypertext
        const string textword = @"(?<textword>[^<>\s]+)";
        const string blank = @"\s+";
        const string non_tag = @"(?:" + textword + @"|" + blank + @")";
        const string a_content = @"(?:" + non_tag + @"|" + non_a_any + @")*";

        // regex that attempts to match a hyperlink
        const string pattern = @"(?i)" + a + a_content + a_end;
        HyperlinkRegex = new Regex(pattern, RegexOptions.Compiled);
    }

    private static string ReadToEnd()
    {
        using (var sr = new StreamReader(Console.OpenStandardInput()))
            return sr.ReadToEnd();
    }

    private static void Main()
    {
        foreach (Match m in HyperlinkRegex.Matches(ReadToEnd())) {
            var url = m.Groups["url"].Value;
            var textwords = m.Groups["textword"].Captures.Cast<Capture>()
                                                         .Select(c => c.Value);

            Console.WriteLine("{0},{1}", url, string.Join(" ", textwords));
        }
    }
}
