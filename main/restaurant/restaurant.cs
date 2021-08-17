using System;

internal static class Solution {
    private static int GreatestCommonDivisor(int m, int n)
    {
        return n == 0 ? m : GreatestCommonDivisor(n, m % n);
    }

    private static void Main()
    {
        for (var t = int.Parse(Console.ReadLine()); t > 0; --t) {
            var lb = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
            var length = lb[0];
            var breadth = lb[1];

            var gcd = GreatestCommonDivisor(length, breadth);
            var ans = length * breadth / (gcd * gcd);
            Console.WriteLine(ans);
        }
    }
}
