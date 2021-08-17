import java.util.Scanner;
import java.util.stream.IntStream;

final class Solution {
    private static int[] getSortedRecord(final Scanner sc, final int n)
    {
        return IntStream.range(0, n).map(i -> sc.nextInt()).sorted().toArray();
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int n = sc.nextInt();
                final int[] a = getSortedRecord(sc, n);
                final int[] b = getSortedRecord(sc, n);
                System.out.println(Arrays.equals(a, b) ? '1' : '0');
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
