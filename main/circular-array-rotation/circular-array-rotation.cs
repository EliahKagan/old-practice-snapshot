using static System.Console;

internal static class Solution {
    private static int[] GetRecord()
            => System.Array.ConvertAll(ReadLine().Split(' '), int.Parse);

    private static int CommonResidue(int p, int q) => (q + p % q) % q;

    private static void Main()
    {
        var nkq = GetRecord();

        var n = nkq[0];
        var k = nkq[1];
        var q = nkq[2];

        var a = GetRecord();

        while (q-- > 0) {
            var m = int.Parse(ReadLine());
            var i = CommonResidue(m - k, n);
            WriteLine(a[i]);
        }
    }
}
