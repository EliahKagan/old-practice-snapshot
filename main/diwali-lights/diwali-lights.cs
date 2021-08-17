using System;

internal static class Solution {
    private static int GetNumber()
    {
        return int.Parse(Console.ReadLine());
    }

    private static void Main()
    {
        const int mod = 100000;

        for (var t = GetNumber(); t > 0; --t) {
            var p = 1;

            for (var n = GetNumber(); n > 0; --n)
                p = p * 2 % mod;

            Console.WriteLine((p - 1) % mod);
        }
    }
}
