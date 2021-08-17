import java.util.Scanner;

final class Solution {
    private static int[] get(final Scanner sc)
    {
        final int[] a = new int[sc.nextInt()];
        for (int i = 0; i != a.length; ++i) a[i] = sc.nextInt();
        return a;
    }
    
    private static boolean isSortedUnique(final int[] a)
    {
        for (int i = 1; i != a.length; ++i)
            if (a[i] <= a[i - 1]) return false;
        
        return true;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(isSortedUnique(get(sc)) ? 1 : 0);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
