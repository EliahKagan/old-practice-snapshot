using static System.Console;
using static System.Linq.Enumerable;

internal static class Solution {
    private static int[] GetRecord()
            => System.Array.ConvertAll(ReadLine().Split(' '), int.Parse);

    private static int CountDivisibleSumPairs(int[] a, int n, int k)
    {
        return Range(0, n - 1)
                .Sum(i => Range(i + 1, n - i - 1)
                            .Count(j => (a[i] + a[j]) % k == 0));
    }

    private static void Main()
    {
        var nk = GetRecord();
        WriteLine(CountDivisibleSumPairs(GetRecord(), nk[0], nk[1]));
    }
}
