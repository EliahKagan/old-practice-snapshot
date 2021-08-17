using System.Linq;
using static System.Console;

internal static class Solution {
    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(ReadLine()))) {
            WriteLine(ReadLine().Intersect(ReadLine()).Count() > 0 ? "YES"
                                                                   : "NO");
        }
    }
}
