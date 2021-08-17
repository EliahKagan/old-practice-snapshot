final class Solution {
    private static int[] fibonacci(final int max_index, final int mod)
    {
        final int[] fib = new int[max_index + 1];
        
        fib[0] = 0;
        fib[1] = 1;
        
        for (int i = 2; i <= max_index; ++i)
            fib[i] = (fib[i - 2] + fib[i - 1]) % mod;
        
        return fib;
    }
    
    public static void main(final String[] args)
    {
        final int nmax = 1000, base = 10;
        final int[] fib = fibonacci(nmax, base);
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(fib[sc.nextInt()]);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
