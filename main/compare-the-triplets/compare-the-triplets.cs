using System;
using System.Linq;

internal static class Solution {
    private static int[] GetRecord()
            => Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

    private static void Main()
    {
        var a = GetRecord();
        var b = GetRecord();

        var ascore = 0;
        var bscore = 0;

        foreach (var i in Enumerable.Range(0, a.Length)) {
            if (a[i] == b[i]) continue;

            if (a[i] > b[i])    ++ascore;
            else                ++bscore;
        }

        Console.WriteLine("{0} {1}", ascore, bscore);
    }
}
