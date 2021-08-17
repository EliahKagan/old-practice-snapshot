import java.util.Scanner;
import java.util.stream.IntStream;

final class Solution {
    private static int[] readSortedRecord(final Scanner sc)
    {
        return IntStream.range(0, sc.nextInt())
                        .map(i -> sc.nextInt())
                        .sorted()
                        .toArray();
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int[] a = readSortedRecord(sc);
                final int i = sc.nextInt(), j = sc.nextInt();
                
                System.out.println(IntStream.range(i, j - 1)
                                            .map(k -> a[k])
                                            .sum());
            }
        }
    }
}
