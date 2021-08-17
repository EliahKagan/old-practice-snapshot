using System.Linq;
using static System.Array;
using static System.Console;
using static System.Math;

internal static class Solution {
    private static void Main()
    {
        var n = double.Parse(ReadLine());
        var a = ConvertAll(ReadLine().Split(' '), int.Parse);

        var mean = a.Sum() / n;
        var stddev = Sqrt(a.Select(ai => ai - mean).Sum(d => d * d) / n);

        WriteLine("{0:F1}", stddev);
    }
}
