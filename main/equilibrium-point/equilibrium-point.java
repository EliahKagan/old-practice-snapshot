import java.util.Scanner;

final class Solution {
    private static final int NO_EQUILIBRIUM = -1;
    
    private static int readArrayAndFindEquilibrium(final Scanner sc)
    {
        final int[] a = new int [sc.nextInt()];
        int right = 0;
        for (int i = 0; i != a.length; ++i) right += a[i] = sc.nextInt();
        
        for (int left = 0, i = 0; i != a.length; left += a[i++])
            if (left == (right -= a[i])) return i + 1;
        
        return NO_EQUILIBRIUM;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(readArrayAndFindEquilibrium(sc));
        }
    }
}
