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
    
    // Create a new (zero) matrix.
    public Matrix(final long mod, final int m, final int n)
    {
        if (mod <= 0 || m <= 0 || n <= 0) throw new IllegalArgumentException();
        
        MOD = mod;
        M = m;
        N = n;
        ent = new long[m * n];
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
    private static void print(final Matrix mat)
    {
        for (int i = 1; i <= mat.M; ++i) {
            for (int j = 1; j <= mat.N; ++j)
                System.out.format(" %d", mat.get(i, j));
            
            System.out.println();
        }
    }
    
    private static void mul_test()
    {
        final long mod = 1_000_000_007L;
        
        final Matrix mat = new Matrix(mod, 3, 3,
                                      1L, 2L, 3L, 4L, 5L, 6L, 7L, 8L, 9L);
        print(mat);
        System.out.println();
        
        final Matrix u = new Matrix(mod, 3, 1, 10L, 11L, 12L);
        print(u);
        System.out.println();
        
        final Matrix v = mat.mul(u);
        print(v);
    }
    
    private static void pow_test()
    {
        final long a = 1L, b = 1L, c = 0L, mod = 100 /*1_000_000_007L*/;
        
        final Matrix seed = new Matrix(mod, 3, 1, 1L,
                                                  1L, 
                                                  c);
        
        final Matrix operator = new Matrix(mod, 3, 3, a,  b,  1L,
                                                      1L, 0L, 0L,
                                                      0L, 0L, 1L);
        
        for (int i = 1; i <= 40; ++i)
            System.out.format(" %d", operator.pow(i).mul(seed).get(1, 1));
        
        System.out.println();
    }
    
    public static void main(final String[] args)
    {
        mul_test();
        pow_test();
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
