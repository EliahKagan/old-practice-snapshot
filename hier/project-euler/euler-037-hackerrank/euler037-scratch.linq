<Query Kind="Program" />

internal static class Arithmetic {
    private const int Billion = 1000000000; // highest power of 10 int can fit

    private static readonly int[] PowersOf10 = ComputePowersOf10().ToArray();

    private static IEnumerable<int> ComputePowersOf10()
    {
        for (var i = 1; ; i *= 10) {
            yield return i;
            if (i == Billion) yield break;
        }
    }

    // Returns the highest power of 10 strictly less than n. Assumes n > 1.
    internal static int PrevPowerOf10(int n)
    {
        var i = Array.BinarySearch(PowersOf10, n);
        return PowersOf10[(i < 0 ? ~i : i) - 1];
    }
    
    private static void Main()
    {
        var r = Enumerable.Range(2, 10000);
        r.Zip(r.Select(PrevPowerOf10), (Val, PrevPower) => new { Val, PrevPower }).Dump();
    }
}