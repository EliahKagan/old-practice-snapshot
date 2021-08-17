// (Sum[k=1..n]k)^2 - Sum[k=1..n](k^2) = (1/4)(n^2)(n+1)^2 - (1/6)n(n+1)(2n+1)
//                                     = (1/12)n(n+1)(3n+2)(n-1)

using static System.Console;
using static System.Math;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static void Main()
    {
        for (var t = int.Parse(ReadLine()); t > 0; --t) {
            var n = long.Parse(ReadLine());
            WriteLine(Abs(n * (n + 1L) * (n * 3L + 2L) * (n - 1L) / 12L));
        }
    }
}
