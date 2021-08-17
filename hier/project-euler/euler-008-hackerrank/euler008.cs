#define DEBUG

using System.Linq;
using static System.Array;
using static System.Console;
using static System.Diagnostics.Contracts.Contract;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static int MaxContiguousProduct(int[] digits, int width)
    {
        var n = digits.Length;
        Assert(width <= n);

        var zeros = 0;
        var cur = 1;

        var j = 0;
        for (; j != width; ++j) {
            if (digits[j] == 0) ++zeros;
            else cur *= digits[j];
        }

        var max = (zeros == 0 ? cur : 0);

        for (var i = 0; j != n; ++i, ++j) {
            if (digits[i] == 0) --zeros;
            else cur /= digits[i];

            if (digits[j] == 0) ++zeros;
            else cur *= digits[j];

            if (zeros == 0 && max < cur) max = cur;
        }

        return max;
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(ReadLine()))) {
            var nk = ConvertAll(ReadLine().Split(' '), int.Parse);
            var digits = ReadLine().Trim().Select(c => c - '0').ToArray();
            Assert(digits.Length == nk[0]);
            WriteLine(MaxContiguousProduct(digits, nk[1]));
        }
    }
}
