final class Solution {
    private static final int MOD = 1_000_000_007;
    
    private static int[] getLucasSequence(final int size)
    {
        if (size < 2) throw new IllegalArgumentException();
        
        final int[] a = new int[size];
        
        a[0] = 2;
        a[1] = 1;
        
        for (int i = 2; i != size; ++i)
            a[i] = (a[i - 2] + a[i - 1]) % MOD;
        
        return a;
    }
    
    public static void main(final String[] args)
    {
        final int max = 100;
        final int[] a = getLucasSequence(max + 1);
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(a[sc.nextInt()]);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
