using System;
using System.Linq;
using System.Text.RegularExpressions;

internal static class Solution {
    private static void Main()
    {
        var langs = "C|CPP|JAVA|PYTHON|PERL|PHP|RUBY|CSHARP|HASKELL|CLOJURE|"
                  + "BASH|SCALA|ERLANG|CLISP|LUA|BRAINFUCK|JAVASCRIPT|GO|D|"
                  + "OCAML|R|PASCAL|SBCL|DART|GROOVY|OBJECTIVEC";

        var regex = new Regex(string.Format(@"^\d+\s+({0})\s*$", langs));

        foreach (var i in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            Console.WriteLine(regex.IsMatch(Console.ReadLine()) ? "VALID"
                                                                : "INVALID");
        }
    }
}
