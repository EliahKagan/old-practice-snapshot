using System;

internal static class Solution {
    private static void Main()
    {
        const long mod = 1000000007;

        for (var t = int.Parse(Console.ReadLine()); t > 0; --t) {
            var n = long.Parse(Console.ReadLine()) % mod;
            Console.WriteLine((n * n) % mod);
        }
    }
}
