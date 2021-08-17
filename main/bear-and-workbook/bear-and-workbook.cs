#define DEBUG

using System;
using System.Diagnostics.Contracts;

internal static class Solution {
    private static int[] GetRecord(int assert_count)
    {
        var rec = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Contract.Assert(rec.Length == assert_count);
        Contract.Assert(Array.TrueForAll(rec, i => 0 < i && i <= 100));
        return rec;
    }

    private static int At(this int[] self, int index)
    {
        return self[index - 1];
    }

    private static int CountSpecials(int n, int k, int[] t)
    {
        var specials = 0;
        var page = 0;

        for (var chapter = 1; chapter <= n; ++chapter) {
            var space = 0;

            for (var problem = 1; problem <= t.At(chapter); ++problem) {
                if (space == 0) {
                    ++page;
                    space = k;
                }

                --space;
                if (page == problem) ++specials;
            }
        }

        return specials;
    }

    private static void Main()
    {
        var nk = GetRecord(2);
        var n = nk[0];
        var k = nk[1];

        Console.WriteLine(CountSpecials(n, k, GetRecord(n)));
    }
}
