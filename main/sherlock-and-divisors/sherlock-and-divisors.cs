using System.Runtime.CompilerServices;
using static System.Console;

internal static class Solution {
    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    private static int CountDivisors(int n)
    {
        var count = 1;
        var stop = n;

        for (var i = 2; i < stop; ++i) {
            if (n % i == 0) {
                ++count;
                stop = n / i;
            }
        }

        return n / stop == stop ? count * 2 - 1 : count * 2;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    private static int CountEvenDivisors(int n)
    {
        return n % 2 == 0 ? CountDivisors(n / 2) : 0;
    }

    private static void Main()
    {
        for (var t = int.Parse(ReadLine()); t > 0; --t)
            WriteLine(CountEvenDivisors(int.Parse(ReadLine())));
    }
}
