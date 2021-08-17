using System;
using System.Runtime.CompilerServices;

internal static class Solution {
    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    private static int CountDivisors(int n)
    {
        var count = 0;
        var stop = Convert.ToInt32(Math.Ceiling(Math.Sqrt(n)));

        for (var i = 1; i < stop; ++i)
            if (n % i == 0) ++count;

        return stop * stop == n ? count * 2 + 1 : count * 2;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    private static int CountEvenDivisors(int n)
    {
        return n % 2 == 0 ? CountDivisors(n / 2) : 0;
    }

    private static void Main()
    {
        for (var t = int.Parse(Console.ReadLine()); t > 0; --t) {
            Console.WriteLine(
                    CountEvenDivisors(int.Parse(Console.ReadLine())));
        }
    }
}
