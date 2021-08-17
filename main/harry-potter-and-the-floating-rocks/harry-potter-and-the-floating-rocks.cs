using System;

internal static class Solution {
    private static int GreatestCommonDivisor(int m, int n)
    {
        return n == 0 ? m : GreatestCommonDivisor(n, m % n);
    }

    private static void Main()
    {
        for (var t = int.Parse(Console.ReadLine()); t > 0; --t) {
            var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

            var x1 = a[0];
            var y1 = a[1];
            var x2 = a[2];
            var y2 = a[3];

            var gcd = GreatestCommonDivisor(x1 - x2, y1 - y2);
            Console.WriteLine(gcd == 0 ? 0 : Math.Abs(gcd) - 1);
        }
    }
}
