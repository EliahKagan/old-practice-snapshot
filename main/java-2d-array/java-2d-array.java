final class Solution {
    private static final int M = 6, N = 6;
    
    private static int[][] getGrid()
    {
        final int[][] a = new int[M][N];
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int i = 0; i != M; ++i) {
                for (int j = 0; j != N; ++j)
                    a[i][j] = sc.nextInt();
            }
        }
        
        return a;
    }
    
    private static int hourglassSum(final int[][] a, final int i, final int j)
    {
        return a[i - 1][j - 1] + a[i - 1][j] + a[i - 1][j + 1]
                               + a[i][j]
             + a[i + 1][j - 1] + a[i + 1][j] + a[i + 1][j + 1];
    }
    
    private static int maxHourglassSum(final int[][] a)
    {
        int max = Integer.MIN_VALUE;
        
        final int m = M - 1, n = N - 1;
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j)
                max = Math.max(max, hourglassSum(a, i, j));
        }
        
        return max;
    }
    
    public static void main(final String[] args)
    {
        System.out.format("%d%n", maxHourglassSum(getGrid()));
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
