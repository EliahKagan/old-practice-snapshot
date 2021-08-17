import java.math.BigInteger;

final class Matrix2x1 { // a 2-dimensional column vector
    public final BigInteger e1, e2;
    
    public Matrix2x1(final BigInteger e1, final BigInteger e2)
    {
        this.e1 = e1;
        this.e2 = e2;
    }
    
    public Matrix2x1(final long e1, final long e2)
    {
        this(BigInteger.valueOf(e1), BigInteger.valueOf(e2));
    }
}

final class Matrix2x2 {
    public static final Matrix2x2 ZERO = new Matrix2x2(
            BigInteger.ZERO, BigInteger.ZERO, BigInteger.ZERO, BigInteger.ZERO
    );
    
    public static final Matrix2x2 IDENTITY = new Matrix2x2(
            BigInteger.ONE, BigInteger.ZERO, BigInteger.ZERO, BigInteger.ONE
    );
    
    public final BigInteger e11, e12, e21, e22;
    
    public Matrix2x2(final BigInteger e11, final BigInteger e12,
                     final BigInteger e21, final BigInteger e22)
    {
        this.e11 = e11;
        this.e12 = e12;
        this.e21 = e21;
        this.e22 = e22;
    }
    
    public Matrix2x2(final long e11, final long e12,
                     final long e21, final long e22)
    {
        this(BigInteger.valueOf(e11), BigInteger.valueOf(e12),
             BigInteger.valueOf(e21), BigInteger.valueOf(e22));
    }
    
    public Matrix2x1 mul(final Matrix2x1 vector)
    {
        return new Matrix2x1(
                e11.multiply(vector.e1).add(e12.multiply(vector.e2)),
                e21.multiply(vector.e1).add(e22.multiply(vector.e2)));
    }
    
    public Matrix2x2 mul(final Matrix2x2 matrix)
    {
        return new Matrix2x2(
                e11.multiply(matrix.e11).add(e12.multiply(matrix.e21)),
                e11.multiply(matrix.e12).add(e12.multiply(matrix.e22)),
                e21.multiply(matrix.e11).add(e22.multiply(matrix.e21)),
                e21.multiply(matrix.e12).add(e22.multiply(matrix.e22)));
    }
    
    public Matrix2x2 pow(final int exponent)
    {
        if (exponent < 2) return exponent == 1 ? this : IDENTITY;
        final Matrix2x2 r = pow(exponent / 2), s = r.mul(r);
        return exponent % 2 == 0 ? s : s.mul(this);
    }
}

final class Fibonacci {
    private static final Matrix2x1 SEED = new Matrix2x1(1L, 1L);
    
    private static final Matrix2x2 OPERATOR = new Matrix2x2(1L, 1L, 1L, 0L);
    
    static BigInteger at(final int index)
    {
        return index < 2 ? BigInteger.valueOf(index)
                         : OPERATOR.pow(index - 2).mul(SEED).e1;
    }
    
    private Fibonacci() { } // the Fibonacci class should not be instantiated
}

final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int n = sc.nextInt();
                System.out.println(Fibonacci.at(n).toString().length());
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
