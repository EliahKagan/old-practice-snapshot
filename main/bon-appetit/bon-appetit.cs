using System;
using System.Linq;

internal static class Solution {
    private static int[] GetRecord()
            => Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

    private static void Main()
    {
        var nk = GetRecord();

        var k = nk[1];
        var c = GetRecord();
        var b_charged = int.Parse(Console.ReadLine());

        var b_actual = (c.Sum() - c[k]) / 2;

        if (b_charged > b_actual)   Console.WriteLine(b_charged - b_actual);
        else                        Console.WriteLine("Bon Appetit");
    }
}
