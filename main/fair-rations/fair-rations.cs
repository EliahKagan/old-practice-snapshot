using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        Console.ReadLine(); // don't need n
        var b = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);

        if (b.Sum() % 2 == 0) {
            var k = 0;

            foreach (var i in Enumerable.Range(0, b.Length - 1)) {
                if (b[i] % 2 != 0) {
                    ++b[i + 1];
                    ++k;
                }
            }

            Console.WriteLine(k * 2);
        }
        else Console.WriteLine("NO");
    }
}
