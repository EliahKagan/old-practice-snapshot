using System;

internal static class Solution {
    private static long[] GetRecord()
    {
        return Array.ConvertAll(Console.ReadLine().Split(' '), long.Parse);
    }

    private static void Main()
    {
        var nm = GetRecord();
        var n = nm[0];
        var m = nm[1];

        var sum = 0L;

        for (; m > 0; --m) {
            var abk = GetRecord();
            var a = abk[0];
            var b = abk[1];
            var k = abk[2];

            sum += (b - a + 1L) * k;
        }

        Console.WriteLine(sum / n);
    }
}
