public class Solution {
    private const long Mod = 1337L;

    private static long SuperPow(long bas, BigInteger exp) {
        if (exp.IsZero) return 1L;

        var r = SuperPow(bas, exp >> 1);
        r *= r;
        if (!exp.IsEven) r *= bas;
        return r % Mod;
    }

    public int SuperPow(int a, int[] b) {
        var sb = new StringBuilder(b.Length, b.Length);
        foreach (var d in b) sb.Append(d);
        return (int)SuperPow(a, BigInteger.Parse(sb.ToString()));
    }
}
