import java.util.BitSet;
import java.util.Scanner;
import java.util.StringJoiner;
import java.util.stream.IntStream;

final class Primes {
    private final int[] elems;
    
    public Primes(final int n)
    {
        final int len = (n + 1) / 2;
        final BitSet bits = new BitSet(len);
        bits.set(0, len);

        final int istop = (int)Math.sqrt(n) / 2 + 1;
        for (int i = 1; i != istop; ++i) {
            if (bits.get(i)) {
                final int jstep = i * 2 + 1;
                for (int j = (i + 1) * i * 2; j < len; j += jstep)
                    bits.clear(j);
            }
        }
        
        elems = IntStream.concat(IntStream.of(2),
                    bits.stream().skip(1L).map(i -> i * 2 + 1)).toArray();
    }
    
    public IntStream range(final int lowerBound, final int upperBound)
    {
        final int i = java.util.Arrays.binarySearch(elems, lowerBound);
        final int fromIndex = i < 0 ? ~i : i;
        
        final int j = java.util.Arrays.binarySearch(elems, fromIndex,
                                                    elems.length, upperBound);
        final int toIndex = j < 0 ? ~j : j + 1;
        
        return IntStream.range(fromIndex, toIndex).map(k -> elems[k]);
    }
}

final class Solution {
    public static void main(final String[] args)
    {
        final Primes primes = new Primes(100000000);
        
        try (final Scanner sc
                = new Scanner(System.in).useDelimiter("[\\s-]+")) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final StringJoiner joiner = new java.util.StringJoiner(" ");
                
                final int lowerBound = sc.nextInt(), upperBound = sc.nextInt();
                
                primes.range(lowerBound, upperBound)
                      .forEachOrdered(n -> joiner.add(Integer.toString(n)));
                
                System.out.println(joiner);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
