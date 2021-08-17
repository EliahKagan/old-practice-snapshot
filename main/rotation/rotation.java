import java.util.Scanner;

final class Solution {
    private static int[] readRecord(final Scanner sc)
    {
        final int[] a = new int[sc.nextInt()];
        for (int i = 0; i != a.length; ++i) a[i] = sc.nextInt();
        return a;
    }
    
    private static int findRotationOffset(final int[] a)
    {
        int i = 1;
        while (i < a.length && a[0] == a[i]) ++i;
        while (i < a.length && a[0] < a[i]) ++i;
        return i == a.length ? 0 : i;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(findRotationOffset(readRecord(sc)));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
