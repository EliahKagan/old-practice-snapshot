final class Solution {
    private static final int MOD = 1_000_000_007;
    
    private static int[] getPadovanSequence(final int size)
    {
        if (size < 3) throw new IllegalArgumentException();
        
        final int[] a = new int[size];
        a[0] = a[1] = a[2] = 1;
        
        for (int i = 3; i != size; ++i)
            a[i] = (a[i - 3] + a[i - 2]) % MOD;
        
        return a;
    }
    
    public static void main(final String[] args)
    {
        final int max = 100;
        final int[] a = getPadovanSequence(max + 1);
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(a[sc.nextInt()]);
        }
    }
}
