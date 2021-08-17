using System.Linq;
using static System.Console;
using static System.Math;

internal static class Solution {
    private static void Main()
    {
        var n = double.Parse(ReadLine());
        var bins = ReadLine().Split(' ').GroupBy(s => Sign(int.Parse(s)));

        foreach (var sign in new[] { 1, -1, 0 }) {
            WriteLine("{0:F6}", bins.Where(g => g.Key == sign)
                                    .SelectMany(g => g)
                                    .Count() / n);
        }
    }
}
