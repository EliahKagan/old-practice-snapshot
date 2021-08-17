using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

[assembly: System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Solution {
    private static Regex TagWithAttributesRegex
    {
        get {
            const string name = @"([a-z][a-z\d]*)"; // of tag or attribute
            const string val = @"(?:=(?:[^<>""'\s]*|""[^""]*""|'[^']*'))?";
            const string attrs = @"(?:\s+" + name + val + @")*";
            const string pattern = @"<" + name + attrs + @"\s*(?:/\s*)?>";

            return new Regex(pattern, RegexOptions.Compiled);
        }
    }

    private static SortedDictionary<string, SortedSet<string>>
    ReadAllLinesAsOrderedTagAttributeDictionary()
    {
        var attrs = new SortedDictionary<string, SortedSet<string>>();
        var regex = TagWithAttributesRegex;

        foreach (var n in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var line = Console.ReadLine().ToLowerInvariant();

            foreach (Match m in regex.Matches(line)) {
                var tag = m.Groups[1].Value;

                if (!attrs.ContainsKey(tag))
                    attrs.Add(tag, new SortedSet<string>());

                foreach (Capture c in m.Groups[2].Captures)
                    attrs[tag].Add(c.Value);
            }
        }

        return attrs;
    }

    private static void Main()
    {
        foreach (var p in ReadAllLinesAsOrderedTagAttributeDictionary())
            Console.WriteLine("{0}:{1}", p.Key, string.Join(",", p.Value));
    }
}
