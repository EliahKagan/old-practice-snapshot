#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        var nk = Console.ReadLine().Split(' ');
        var n = int.Parse(nk[0]);
        var k = long.Parse(nk[1]);

        var toys = Array.ConvertAll(Console.ReadLine().Split(' '), long.Parse);
        Contract.Assert(toys.Length == n);
        Array.Sort(toys);

        var cost = 0L;
        var i = 0;
        while ((cost += toys[i]) <= k) ++i;

        Console.WriteLine(i);
    }
}
