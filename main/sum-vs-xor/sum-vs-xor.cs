using static System.Console;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    // Computes the number of distinct ways to set zero or more 0s in the
    // binary representation of n to 1s without exceeding n itself.
    private static long CountEqualXorAndSum(long n)
    {
        var zeros = 0;
        for (; n != 0L; n >>= 1)
            if ((n & 1L) == 0L) ++zeros;

        var ways = 1L;
        while (zeros-- > 0) ways <<= 1;
        return ways;
    }

    private static void Main()
            => WriteLine(CountEqualXorAndSum(long.Parse(ReadLine())));
}
