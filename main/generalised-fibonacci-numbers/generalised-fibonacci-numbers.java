import java.util.Scanner;

final class Matrix {
    public final int M, N; // number of rows, columns
    public final long MOD; // arithmetic on entries is modulo this number
    
    // Creates a matrix view of the entries array.
    // Note that some operations [currently pow()] assume it doesn't change.
    public Matrix(final long mod, final int m, final int n,
                  final long... entries)
    {
        if (mod <= 0 || m <= 0 || n <= 0 || m * n != entries.length)
            throw new IllegalArgumentException();
        
        MOD = mod;
        M = m;
        N = n;
        ent = entries;
    }
    
    public long get(final int i, final int j)
    {
        return ent[idx(i, j)];
    }
    
    public Matrix mul(final Matrix rhs)
    {
        if (MOD != rhs.MOD || N != rhs.M) throw new IllegalArgumentException();
        
        final Matrix ret = new Matrix(MOD, M, rhs.N);
        
        for (int i = 1; i <= M; ++i) {
            for (int k = 1; k <= rhs.N; ++k) {
                long e = 0L;
                
                for (int j = 1; j <= N; ++j)
                    e = (e + get(i, j) * rhs.get(j, k) % MOD) % MOD;
                
                ret.set(i, k, e);
            }
        }
        
        return ret;
    }
    
    public Matrix pow(final int exponent)
    {
        if (exponent < 2) {
            if (exponent < 1) throw new IllegalArgumentException();
            return this;
        }
        
        final Matrix r = pow(exponent / 2), s = r.mul(r);
        return exponent % 2 == 0 ? s : s.mul(this);
    }
    
    // Create a new (zero) matrix.
    protected Matrix(final long mod, final int m, final int n)
    {
        if (mod <= 0 || m <= 0 || n <= 0) throw new IllegalArgumentException();
        
        MOD = mod;
        M = m;
        N = n;
        ent = new long[m * n];
    }
    
    protected void set(final int i, final int j, final long value)
    {
        ent[idx(i, j)] = value;
    }
    
    private final long[] ent;
    
    private int idx(final int i, final int j)
    {
        if (i <= 0 || i > M || j <= 0 || j > N)
            throw new IndexOutOfBoundsException();
        
        return (i - 1) * N + (j - 1);
    }
}

final class Solution {
    private static long g(final long a, final long b, final long c,
                          final int n, final long mod)
    {
        if (n < 3) return 1L;
        
        final Matrix seed = new Matrix(mod, 3, 1, 1L,
                                                  1L,
                                                  c);
        
        final Matrix operator = new Matrix(mod, 3, 3, a,  b,  1L,
                                                      1L, 0L, 0L,
                                                      0L, 0L, 1L);
        
        return operator.pow(n - 2).mul(seed).get(1, 1);
    }
    
    private static void run(final Scanner sc)
    {
        final long a = sc.nextLong(), b = sc.nextLong(), c = sc.nextLong();
        final int n = sc.nextInt();
        System.out.println(g(a, b, c, n, sc.nextLong()));
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) run(sc);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
