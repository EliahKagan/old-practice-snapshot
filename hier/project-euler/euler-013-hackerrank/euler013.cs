using System.Numerics;
using static System.Console;
using static System.Linq.Enumerable;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static void Main()
    {
        const int prefix_length = 10;

        WriteLine(Range(0, int.Parse(ReadLine()))
                    .Select(i => BigInteger.Parse(ReadLine()))
                    .Aggregate(BigInteger.Zero, BigInteger.Add)
                    .ToString("R").Substring(0, prefix_length));
    }
}
