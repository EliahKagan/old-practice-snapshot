using System;

internal static class Solution {
    private static void Main()
    {
        for (var t = int.Parse(Console.ReadLine()); t > 0; --t) {
            var record = Console.ReadLine().Split(' ');

            var a = double.Parse(record[0]);
            var b = double.Parse(record[1]);
            var x = int.Parse(record[2]);

            var power = Math.Pow(a, b);
            var quotient = power / x;

            var m = Convert.ToInt32(Math.Floor(quotient)) * x;
            var n = Convert.ToInt32(Math.Ceiling(quotient)) * x;
            var p = Convert.ToInt32(power);

            Console.WriteLine(p - m <= n - p ? m : n);
        }
    }
}
