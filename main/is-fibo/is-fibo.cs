using System.Collections.Generic;
using static System.Console;

internal static class Solution {
    private static HashSet<long> Fibo = new HashSet<long> { 0L, 1L };

    static Solution()
    {
        var a = 1L;
        var b = 2L;

        while (b <= 10000000000L) {
            Fibo.Add(b);
            var tmp = a;
            a = b;
            b += tmp;
        }
    }

    private static void Main()
    {
        for (var t = int.Parse(ReadLine()); t > 0; --t) {
            WriteLine(Fibo.Contains(long.Parse(ReadLine())) ? "IsFibo"
                                                            : "IsNotFibo");
        }
    }
}
