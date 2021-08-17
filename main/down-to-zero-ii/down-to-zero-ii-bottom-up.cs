using System;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.1")]

internal static class Solution {
    private static int[] TabulateStepsToZero(long nmax)
    {
        var size = nmax + 1L;

        var tab = Enumerable.Repeat(int.MaxValue, (int)size).ToArray();
        tab[0] = 0;
        tab[1] = 1;

        for (var big_factor = 2L; big_factor != size; ++big_factor) {
            tab[big_factor] = Math.Min(tab[big_factor],
                                       tab[big_factor - 1] + 1);

            var max_product = Math.Min(big_factor * big_factor, nmax);

            for (var product = big_factor; product <= max_product;
                                           product += big_factor)
                tab[product] = Math.Min(tab[product], tab[big_factor] + 1);
        }

        return tab;
    }

    private static int GetVal() => int.Parse(Console.ReadLine());

    private static void Main()
    {
        const int nmax = 1000000;
        var tab = TabulateStepsToZero(nmax);
        for (var q = GetVal(); q > 0; --q) Console.WriteLine(tab[GetVal()]);
    }
}
