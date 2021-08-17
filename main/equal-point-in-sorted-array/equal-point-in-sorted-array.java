import java.util.Scanner;
import java.util.stream.IntStream;

final class Solution {
    private static final int NOT_FOUND = -1;
    
    private static int[] readRecord(final Scanner sc)
    {
        return IntStream.range(0, sc.nextInt())
                        .map(i -> sc.nextInt())
                        .toArray();
    }
    
    private static int findEqualPoint(final int[] a) // assumes a is sorted
    {
        final int[] b = IntStream.of(a).distinct().toArray();
        if (b.length % 2 == 0) return NOT_FOUND;
        
        final int key = b[b.length / 2];
        int i = java.util.Arrays.binarySearch(a, key);
        if (i < 0) throw new IllegalArgumentException();
        
        while (i != 0 && a[i - 1] == key) --i;
        return i;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(findEqualPoint(readRecord(sc)));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
