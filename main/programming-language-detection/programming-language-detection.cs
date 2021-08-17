// This resubmission fixes unescaped "." bugs in the "c" and "java1" regexes.
// The old code passed all test cases but would presumably fail in somewhat
// more real-life scenarios than this corrected version. (Of course, both are
// brittle -- real programming language detection is complex, subtle, and
// should probably not be implemented entirely with regular expressions.)

using System;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    private static void Main()
    {
        // This is a VERY rough heuristic. For example, I often write a .java
        // file without imports (or they're not from a package that starts
        // "java") that doesn't contain my entry point class. And a C
        // translation unit may forward-declare all the external symbols it
        // uses and thus require no #include directive. (And of course this
        // doesn't handle quoting, odd formatting, and many other quite common
        // constructs.) Please don't really use this code!
        var c = new Regex(@"^\s*#include\s*(<\S+\.h>|""\S+\.h"")\s*$");
        var java1 = new Regex(@"^\s*import\s+java\w?(\.(\w+|\*))*\s*;\s*$");
        var java2 = new Regex(@"^\s*public\s+static\s+void\s+main\s*\(\s*"
                            + @"(java\s*\.\s*lang\s*\.\s*)?String\s*\[\s*\]\s*"
                            + @"[A-Za-z_]\w*\)\s*\{?\s*$");

        string lang = null;
        string line;

        while (lang == null && (line = Console.ReadLine()) != null) {
            if (c.IsMatch(line))
                lang = "C";
            else if (java1.IsMatch(line) || java2.IsMatch(line))
                lang = "Java";
        }

        Console.WriteLine(lang ?? "Python");
    }
}
