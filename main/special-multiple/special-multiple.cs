using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static IEnumerable<long> ComputeSpecialNumbers()
    {
        const long xmax = 9000000999999L;

        long x;
        var bits = 1L;

        do {
            x = long.Parse(Convert.ToString(bits++, 2).Replace('1', '9'));
            yield return x;
        }
        while (x < xmax);
    }

    private static IEnumerable<long> ComputeAnswers()
    {
        const long nmax = 500L;

        var xs = ComputeSpecialNumbers().ToArray();

        yield return 0L;
        for (var n = 1L; n <= nmax; ++n)
            yield return xs.First(x => x % n == 0);
    }

    private static int Get() => int.Parse(Console.ReadLine());

    private static void Main()
    {
        var ans = ComputeAnswers().ToArray();
        for (var t = Get(); t > 0; --t) Console.WriteLine(ans[Get()]);
    }
}
