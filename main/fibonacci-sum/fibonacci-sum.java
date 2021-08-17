final class Solution {
    private static final int MOD = 1_000_000_007, IMAX = 100_000;
    
    private static int[] fibonacciSums = getFibonacciSums();
    
    private static int[] computeFibonacci()
    {
        final int[] fib = new int[IMAX + 1];
        fib[0] = 0;
        fib[1] = 1;
        
        for (int i = 2; i != fib.length; ++i)
            fib[i] = (fib[i - 2] + fib[i - 1]) % MOD;
        
        return fib;
    }
    
    private static void runningSumInPlace(final int[] a) // needs a.length > 0
    {
        for (int i = 1; i != a.length; ++i) a[i] = (a[i] + a[i - 1]) % MOD;
    }
    
    private static int[] getFibonacciSums()
    {
        final int[] a = computeFibonacci();
        runningSumInPlace(a);
        return a;
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(fibonacciSums[sc.nextInt()]);
        }
    }
}
