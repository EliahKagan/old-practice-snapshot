final class FibonacciPair {
    public final int a, b;
    
    public FibonacciPair(final int a, final int b)
    {
        this.a = a;
        this.b = b;
    }
    
    public FibonacciPair next()
    {
        return new FibonacciPair(b, a + b);
    }
}

final class Solution {
    private static int[] computeNonFibonacci(final int length)
    {
        final int[] seq = new int[length];
        
        FibonacciPair p = new FibonacciPair(3, 5);
        int x = p.a + 1;
        
        for (int i = 0; i != length; ++i) {
            if (x == p.b) {
                p = p.next();
                x = p.a + 1;
            }
            
            seq[i] = x++;
        }
        
        return seq;
    }
    
    public static void main(final String[] args)
    {
        final int nmax = 100_000;
        final int[] seq = computeNonFibonacci(nmax);
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(seq[sc.nextInt() - 1]);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
