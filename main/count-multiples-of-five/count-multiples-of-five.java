import java.util.Scanner;

final class Solution {
    private static void query(int q, final int[] a, final Scanner sc)
    {
        for (String sep = ""; q > 0; --q) {
            final int i = sc.nextInt(), j = sc.nextInt();
            System.out.format("%s%d", sep, a[j] - a[i - 1]);
            sep = " ";
        }
        
        System.out.println();
    }
    
    private static void run(final Scanner sc)
    {
        final int[] a = new int[sc.nextInt() + 1];
        final int q = sc.nextInt();
        
        for (int i = 1; i < a.length; ++i)
            a[i] = sc.nextInt() % 5 == 0 ? a[i - 1] + 1 : a[i - 1];
        
        query(q, a, sc);
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) run(sc);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
