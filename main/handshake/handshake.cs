using System;

internal static class Solution {
    private static int GetNumber()
    {
        return int.Parse(Console.ReadLine());
    }

    private static void Main()
    {
        for (var t = GetNumber(); t > 0; --t) {
            var n = GetNumber();
            Console.WriteLine(n * (n - 1) / 2);
        }
    }
}
