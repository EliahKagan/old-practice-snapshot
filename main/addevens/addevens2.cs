// addevens2.cs - sum even entries in arrays, checking for overflow

using System;
using System.Linq;

[assembly:System.Reflection.AssemblyVersion("0.1.0.1")]

internal static class Seq {
    internal static int SumEvens(int[] seq)
    {
        return (from k in seq where k % 2 == 0 select k).Sum();
    }

    internal static long LongSumEvens(int[] seq)
    {
        return (from k in seq where k % 2 == 0 select (long)k).Sum();
    }
}

internal static class UnitTest {

    private static void Test<T>(Func<int[], T> func, params int[][] seqs)
    {
        foreach (var seq in seqs) {
            try {
                Console.WriteLine(func(seq));
            }
            catch (OverflowException) {
                Console.WriteLine("Overflow!");
            }
        }
    }

    private static void Main()
    {
        int[] a = { int.MaxValue, int.MinValue, int.MaxValue };
        int[] b = { int.MinValue, int.MaxValue, int.MinValue };

        Test(Seq.SumEvens, a, b);
        Test(Seq.LongSumEvens, a, b);
    }
}
