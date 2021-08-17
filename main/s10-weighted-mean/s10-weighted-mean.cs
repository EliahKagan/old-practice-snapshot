using System.Linq;
using System.Collections.Generic;
using static System.Console;

internal static class Solution {
    private static IEnumerable<int> ReadRecord()
            => ReadLine().Split(' ').Select(int.Parse);

    private static double WeightedSum(IEnumerable<int> x, IEnumerable<int> w)
            => x.Zip(w, (xi, wi) => xi * wi).Sum();

    private static double WeightedMean(IEnumerable<int> x, IEnumerable<int> w)
            => (double)WeightedSum(x, w) / w.Sum();

    private static void Main()
    {
        ReadLine(); // don't need n
        var values = ReadRecord();
        var weights = ReadRecord();

        WriteLine("{0:F1}", WeightedMean(values, weights));
    }
}
