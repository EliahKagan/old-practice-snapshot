using static System.Console;
using static System.Linq.Enumerable;

internal static class Solution {
    private static void Main()
    {
        foreach (var n in Range(0, int.Parse(ReadLine())))
            WriteLine(ReadLine().Trim().Distinct().Count());
    }
}
