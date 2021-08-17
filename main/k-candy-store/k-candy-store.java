final class Solution {
    static int[][] computeBinomialCoefficientsModulo(int size, final int mod)
    {
        if (size < 2) size = 2;
        
        final int[][] c = new int[size][size];
        c[0][0] = c[1][0] = c[1][1] = 1;
        
        for (int n = 2; n != size; ++n) {
            c[n][0] = c[n][n] = 1;
            
            for (int r = 1; r != n; ++r)
                c[n][r] = (c[n - 1][r - 1] + c[n - 1][r]) % mod;
        }
        
        return c;
    }
    
    public static void main(final String[] args)
    {
        final int mod = 1000000000;
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            final int t = sc.nextInt();
            final int[] ns = new int[t], ks = new int[t];
            
            int max = 1;
            for (int i = 0; i != t; ++i) {
                ns[i] = sc.nextInt();
                ks[i] = sc.nextInt();
                ns[i] += ks[i] - 1;
                if (max < ns[i]) max = ns[i];
            }
            
            final int[][] c = computeBinomialCoefficientsModulo(max + 1, mod);
            for (int i = 0; i != t; ++i) System.out.println(c[ns[i]][ks[i]]);
        }
    }
}
