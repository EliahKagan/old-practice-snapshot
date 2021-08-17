using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var seq = Console.ReadLine().Split(' ').Select(int.Parse).Take(n);

        Action<Func<int, bool>> pfrac = pred =>
                Console.WriteLine("{0:F6}", seq.Count(pred) / (double)n);

        pfrac(k => k > 0);
        pfrac(k => k < 0);
        pfrac(k => k == 0);
    }
}
