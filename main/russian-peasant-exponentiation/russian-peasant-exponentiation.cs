using System;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    // Computes c+id = (a+ib)^k mod m and returns it as { c, d }.
    private static long[] GaussianIntegerExponential(long a, long b,
                                                     long k, long m)
    {
        for (; k % 2L == 0; k /= 2L) { // a+ib <- (a+ib)^2
            var aa = a * a - b * b;
            var bb = a * b * 2L;
            a = (m + aa % m) % m;
            b = (m + bb % m) % m;
        }

        var c = a;
        var d = b;

        while ((k /= 2L) > 0L) {
            {   // always:  a+ib <- (a+ib)^2
                var aa = a * a - b * b;
                var bb = a * b * 2L;
                a = (m + aa % m) % m;
                b = (m + bb % m) % m;
            }

            if (k % 2L != 0) { // then:  c+id <- (c+id)(a+ib)
                var cc = c * a - d * b;
                var dd = c * b + d * a;
                c = (m + cc % m) % m;
                d = (m + dd % m) % m;
            }
        }

        return new[] { c, d };
    }

    private static void Main()
    {
        for (var q = int.Parse(Console.ReadLine()); q > 0; --q) {
            var abkm = Array.ConvertAll(Console.ReadLine().Split(' '),
                                        long.Parse);

            var cd = GaussianIntegerExponential(abkm[0], abkm[1],
                                                abkm[2], abkm[3]);

            Console.WriteLine(string.Join(" ", cd));
        }
    }
}
