// taxicab0.cs - calculates points equidistant from the origin in the
//               taxicab metric

using System;
using System.Collections.Generic;
using System.Linq;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Program {
    // generates points a (taxicab metric) distance d away from the origin
    private static IEnumerable<Tuple<int, int>> Points(int d)
    {
        System.Diagnostics.Contracts.Contract.Assert(d >= 0);

        for (var i = -d; i <= d; ++i) {
            var j = Math.Abs(i) - d;
            yield return Tuple.Create(i, j);
            if (j != 0) yield return Tuple.Create(i, -j);
        }
    }

    private static void Main()
    {
        foreach (var d in Enumerable.Range(0, 10)) {
            Console.Write("{0}:", d);

            foreach (var p in Points(d))
                Console.Write(" ({0},{1})", p.Item1, p.Item2);

            Console.WriteLine();
        }
    }
}
