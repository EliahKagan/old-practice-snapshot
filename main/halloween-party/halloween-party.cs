using System;

internal static class Solution {
    private static void Main()
    {
        for (var t = int.Parse(Console.ReadLine()); t > 0; --t) {
            var k = long.Parse(Console.ReadLine());
            var w = k / 2;
            var h = k - w;
            Console.WriteLine(h * w);
        }
    }
}
