final class Matrix2x2 {
    public static final long MOD = 100L;
    
    public static final Matrix2x2 ZERO = new Matrix2x2(0L, 0L, 0L, 0L);
    
    public static final Matrix2x2 IDENTITY = new Matrix2x2(1l, 0L, 0L, 1L);
    
    public final long e11, e12, e21, e22;
    
    public Matrix2x2(final long e11, final long e12,
                     final long e21, final long e22)
    {
        this.e11 = e11;
        this.e12 = e12;
        this.e21 = e21;
        this.e22 = e22;
    }
    
    public Matrix2x2 Mul(final Matrix2x2 matrix)
    {
        return new Matrix2x2((e11 * matrix.e11 + e12 * matrix.e21) % MOD,
                             (e11 * matrix.e12 + e12 * matrix.e22) % MOD,
                             (e21 * matrix.e11 + e22 * matrix.e21) % MOD,
                             (e21 * matrix.e12 + e22 * matrix.e22) % MOD);
    }
    
    public Matrix2x2 Pow(final long exponent)
    {
        if (exponent < 2L) return exponent == 1L ? this : IDENTITY;
        final Matrix2x2 r = Pow(exponent / 2L), s = r.Mul(r);
        return exponent % 2L == 0L ? s : s.Mul(this);
    }
}

final class Solution {
    private static final Matrix2x2 FIBONACCI = new Matrix2x2(1L, 1L, 1L, 0L);
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(FIBONACCI.Pow(sc.nextLong()).e21);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
