using System;

internal static class Solution {
    private static long GreatestCommonDivisor(long m, long n)
            => n == 0L ? m : GreatestCommonDivisor(n, m % n);
    
    private static void Main()
    {
        for (var t = int.Parse(Console.ReadLine()); t > 0; --t) {
            var mn = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
            Console.WriteLine(GreatestCommonDivisor(mn[0], mn[1]));
        }
    }
}
