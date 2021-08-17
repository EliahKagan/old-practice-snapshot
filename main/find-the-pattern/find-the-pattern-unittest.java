final class Matrix2x1 { // a 2-dimensional column vector
    public final long e1, e2;
    
    public Matrix2x1(final long e1, final long e2)
    {
        this.e1 = e1;
        this.e2 = e2;
    }
}

final class Matrix2x2 {
    public static final long MOD = 1_000_000_007L;
    
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
    
    public Matrix2x1 Mul(final Matrix2x1 vector)
    {
        return new Matrix2x1((e11 * vector.e1 + e12 * vector.e2) % MOD,
                             (e21 * vector.e1 + e22 * vector.e2) % MOD);
    }
    
    public Matrix2x2 Mul(final Matrix2x2 matrix)
    {
        return new Matrix2x2((e11 * matrix.e11 + e12 * matrix.e21) % MOD,
                             (e11 * matrix.e12 + e12 * matrix.e22) % MOD,
                             (e21 * matrix.e11 + e22 * matrix.e21) % MOD,
                             (e21 * matrix.e12 + e22 * matrix.e22) % MOD);
    }
    
    public Matrix2x2 Pow(final int exponent)
    {
        if (exponent < 2) return exponent == 1 ? this : IDENTITY;
        final Matrix2x2 r = Pow(exponent / 2), s = r.Mul(r);
        return exponent % 2 == 0 ? s : s.Mul(this);
    }
}

final class UnitTest {
    private static void print(final Matrix2x2 matrix)
    {
        System.out.format("%10d %10d%n%10d %10d%n",
                          matrix.e11, matrix.e12, matrix.e21, matrix.e22);
    }
    
    public static void main(final String[] args)
    {
        final long[] a = java.util.stream.Stream.of(args)
                            .mapToLong(Long::parseLong).toArray();
        
        final Matrix2x2 b = new Matrix2x2(a[0], a[1], a[2], a[3]);
        print(b);
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (; ; ) {
                System.out.print("> ");
                final int p = Integer.parseInt(sc.nextLine());
                print(b.Pow(p));
            }
        }
    }
    
    private UnitTest() { } // the UnitTest class should not be instantiated
}
