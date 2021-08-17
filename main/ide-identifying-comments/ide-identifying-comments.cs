using System;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    const string EndL = @"\r?\n";

    // matches comments, and line terminators to the right of C-style comments
    private static string Pattern
    {
        get {
            // matches a C-style (multi-line) comment
            const string cstyle = @"((?s)/\*([^*]|\*(?!/))*\*/)";

            // matches a line terminator to the right of a C-style comment
            var cendl = string.Format("(?<={0}.*){1}", cstyle, EndL);

            // matches a C++-style (single-line) comment
            var cppstyle = string.Format("(//.*({0}|$))", EndL);

            return string.Format("(?n){0}|{1}|{2}", cppstyle, cstyle, cendl);
        }
    }

    private static string Matching(this string text, string pattern)
    {
        return string.Concat(from Match m in Regex.Matches(text, pattern)
                             select m.Value);
    }

    private static string ReadToEnd()
    {
        using (var sr = new StreamReader(Console.OpenStandardInput()))
            return sr.ReadToEnd();
    }

    private static void Main()
    {
        var comments = ReadToEnd().Matching(Pattern);

        var lines = Array.ConvertAll(Regex.Split(comments, EndL),
                                     line => line.TrimStart());
                                     

        if (lines.Length != 0) {
            foreach (var i in Enumerable.Range(0, lines.Length - 1))
                Console.WriteLine(lines[i]);

            if (lines[lines.Length - 1].Length != 0)
                Console.WriteLine(lines[lines.Length - 1]);
        }
    }
}
