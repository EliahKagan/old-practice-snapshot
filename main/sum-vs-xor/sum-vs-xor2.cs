using static System.Console;

[assembly: System.Reflection.AssemblyVersion("1.1.0.0")]

internal static class Solution {
    // Computes the number of distinct ways to set zero or more 0s in the
    // binary representation of n to 1s without exceeding n itself.
    private static long CountEqualXorAndSum(long n)
    {
        var k = 1L;
        for (; n != 0L; n >>= 1)
            if ((n & 1L) == 0L) k <<= 1;

        return k;
    }

    private static void Main()
            => WriteLine(CountEqualXorAndSum(long.Parse(ReadLine())));
}
