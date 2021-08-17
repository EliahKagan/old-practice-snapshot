#define DEBUG

using System.Linq;
using static System.Console;
using static System.Diagnostics.Contracts.Contract;

internal static class Solution {
    private static bool ContainsEqualSumCut(this int[] a)
    {
        var left = 0;
        var right = a.Sum();

        var prev = 0;
        foreach (var cur in a) {
            left += prev;
            right -= cur;
            if (left == right) return true;
            prev = cur;
        }

        return false;
    }

    private static int GetOne() => int.Parse(ReadLine());

    private static int[] GetRecord()
    {
        var n = GetOne();
        var a = System.Array.ConvertAll(ReadLine().Split(' '), int.Parse);
        Assert(a.Length == n);
        return a;
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, GetOne()))
            WriteLine(GetRecord().ContainsEqualSumCut() ? "YES" : "NO");
    }
}
