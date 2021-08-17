import java.util.Scanner;
import java.util.stream.IntStream;
import java.util.stream.Stream;

final class Solution {
    private static String getDelimitedSubMultiset(final String[] a, int bits)
    {
        final java.util.StringJoiner sj = new java.util.StringJoiner(" ");
        
        for (int i = 0; bits != 0; bits >>= 1, ++i)
            if ((bits & 1) != 0) sj.add(a[i]);
        
        return sj.toString();
    }
    
    private static Stream<String> getAllDelimitedSubMultisets(final String[] a)
    {
        return IntStream.range(0, 1 << a.length)
                        .mapToObj(i -> getDelimitedSubMultiset(a, i))
                        .distinct();
    }
    
    private static void printSubMultisets(final String[] a)
    {
        getAllDelimitedSubMultisets(a)
                .forEachOrdered(s -> System.out.format("(%s)", s));
        
        System.out.println();
    }
    
    private static String[] readMultiset(final Scanner sc)
    {
        return IntStream.range(0, sc.nextInt())
                        .map(i -> sc.nextInt())
                        .sorted()
                        .mapToObj(String::valueOf)
                        .toArray(String[]::new);
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                printSubMultisets(readMultiset(sc));
        }
    }
    
    private Solution() { } // the Solution class should not be instantated
}
