import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.IntStream;

final class Solution {
    private static int[] get(final Scanner sc, final int n)
    {
        return IntStream.range(0, n).map(i -> sc.nextInt()).toArray();
    }
    
    private static boolean hasPairSum(final int[] a, int j, final int sum)
    {
        final int jstop = a.length - 1;
        
        for (; j != jstop; ++j) {
            final int key = sum - a[j];
            if (key <= a[j]) return false;
            if (Arrays.binarySearch(a, j + 1, a.length, key) >= 0) return true;
        }
        
        return false;
    }
    
    private static boolean hasTripletSum(final int[] a, final int x)
    {
        return IntStream.range(0, a.length - 2)
                        .anyMatch(i -> hasPairSum(a, i + 1, x - a[i]));
    }
    
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int[] nx = get(sc, 2), a = get(sc, nx[0]);
                Arrays.sort(a);
                System.out.println(hasTripletSum(a, nx[1]) ? "1" : "0");
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
