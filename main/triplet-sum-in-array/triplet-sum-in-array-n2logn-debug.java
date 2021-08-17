import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.IntStream;

final class Solution {
    private static int[] get(final Scanner sc, final int n)
    {
        return IntStream.range(0, n).map(i -> sc.nextInt()).toArray();
    }
    
    private static boolean hasPairSum(final int[] a, final int i, final int x)
    {
        System.err.format("hasPairSum:  i = %d, x = %d%n", i, x);
        
        final int jstop = a.length - 1;
        
        for (int j = i + 1; j != jstop; ++j) {
            final int key = x - a[j];
            System.err.format("j = %d, key = %d%n", j, key);
            if (key <= a[j]) return false;
            if (Arrays.binarySearch(a, j + 1, a.length, key) >= 0) return true;
        }
        
        return false;
    }
    
    private static boolean hasTripletSum(final int[] a, final int x)
    {
        System.err.format("hasTripletSum:  x = %d%n", x);
        
        return IntStream.range(0, a.length - 2)
                        .anyMatch(i -> hasPairSum(a, i, x - a[i]));
    }
    
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int[] nx = get(sc, 2), a = get(sc, nx[0]);
                Arrays.sort(a);
                for (final int val : a) System.out.format("%d ", val);
                System.out.println();
                System.out.println(hasTripletSum(a, nx[1]) ? "1" : "0");
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
