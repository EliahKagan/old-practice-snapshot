// ide-identifying-comments-scratch.cs - scratchwork for "IDE Identifying
//     comments" problem on HackerRank (this is not the solution, just notes)

using System;
using System.Linq;
using System.Text.RegularExpressions;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Program {
    private static void Main()
    {
        const string text =
@"/*aa*/quux
// abc
de /* abc*def*//*aab?*/ agfg
ddef
gfdsgfd//gs
dsg/*foo*/
bar
*/dgs
/* a a
bb

fsdagfh

*/ afdgag
q
//abc";

        // matches a line terminator
        const string endl = @"((?m)(?<=$)\s\s?(?=^))";

        // matches a C-style (multi-line) comment
        const string cstyle = @"((?s)/\*([^*]|\*(?!/))*\*/)";

        // matches a line terminator to the right of a C-style comment
        var cendl = string.Format("(?<={0}.*){1}", cstyle, endl);

        // matches a C++-style (single-line) comment
        var cppstyle = string.Format("(//.*({0}|$))", endl);

        // matches comments, and line terminators rightward of C-style comments
        var pattern = string.Format("(?n){0}|{1}|{2}",
                                    cppstyle, cstyle, cendl);

        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.WriteLine(pattern);
        Console.ForegroundColor = ConsoleColor.Gray;
        Console.WriteLine();

        Console.WriteLine(string.Concat(Regex.Matches(text, pattern)
                                             .Cast<Match>()
                                             .Select(m => m.Value)));
    }
}
