final class Arith {
    static int max(int[] a)
    {
        int ret = Integer.MIN_VALUE;
        for (final int x : a)
            if (ret < x) ret = x;
        
        return ret;
    }
    
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
    
    static void printBinomialCoefficientRow(int[][] c, int n)
    {
        for (int r = 0; r != n; ++r) System.out.format("%d ", c[n][r]);
        System.out.println(c[n][n]);
    }
}

final class Solution {
    private static int[] readValues()
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            final int[] ns = new int[sc.nextInt()];
            for (int i = 0; i != ns.length; ++i) ns[i] = sc.nextInt();
            return ns;
        }
    }
    
    public static void main(final String[] args)
    {
        final int mod = 1000000000;
        
        final int[] ns = readValues();
        final int max = Arith.max(ns);
        
        final int[][] c = Arith.computeBinomialCoefficientsModulo(max + 1,
                                                                  mod);
        
        for (final int n : ns) Arith.printBinomialCoefficientRow(c, n);
    }
}
