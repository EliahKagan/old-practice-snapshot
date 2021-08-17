final class Solution {
    private static int[][] computeBinomialCoefficientsModulo(int size)
    {
        if (size < 2) size = 2;
        
        final int[][] c = new int[size][size];
        c[0][0] = c[1][0] = c[1][1] = 1;
        
        for (int n = 2; n != size; ++n) {
            c[n][0] = c[n][n] = 1;
            
            for (int r = 1; r != n; ++r)
                c[n][r] = c[n - 1][r - 1] + c[n - 1][r];
        }
        
        return c;
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            final int t = sc.nextInt();
            final int[] ns = new int[t], rs = new int[t];
            
            int max = 1;
            for (int i = 0; i != t; ++i) {
                ns[i] = sc.nextInt() - 1;
                rs[i] = sc.nextInt() - 1;
                ns[i] += rs[i];
                if (max < ns[i]) max = ns[i];
            }
            
            final int[][] c = computeBinomialCoefficientsModulo(max + 1);
            for (int i = 0; i != t; ++i) System.out.println(c[ns[i]][rs[i]]);
        }
    }
}
