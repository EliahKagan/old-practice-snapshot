using System;
using System.Linq;
using static System.Math;

internal static class Solution {
    private static long[] GetRecord()
    {
        return Array.ConvertAll(Console.ReadLine().Split(' '), long.Parse);
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var bw = GetRecord();
            var xyz = GetRecord();

            var b = bw[0];
            var w = bw[1];
            var x = xyz[0];
            var y = xyz[1];
            var z = xyz[2];

            Console.WriteLine(checked(b * Min(x, y + z) + w * Min(y, x + z)));
        }
    }
}
