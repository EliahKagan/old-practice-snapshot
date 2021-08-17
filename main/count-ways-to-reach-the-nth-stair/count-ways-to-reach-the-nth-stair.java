final class Solution {
    private static int[] Fibonacci(final int n, final int m)
    {
        final int[] a = new int[n + 1];
        a[0] = a[1] = 1;
        for (int i = 2; i <= n; ++i) a[i] = (a[i - 2] + a[i - 1]) % m;
        return a;
    }
    
    public static void main(final String[] args)
    {
        final int[] a = Fibonacci(100, 1000000007);
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(a[sc.nextInt()]);
        }
    }
}
