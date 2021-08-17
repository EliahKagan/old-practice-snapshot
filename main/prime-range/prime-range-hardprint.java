import java.util.stream.IntStream;

final class Primes {
    private final int[] elems;
    
    public Primes(final int n)
    {
        final int len = (n + 1) / 2;
        final java.util.BitSet bits = new java.util.BitSet(len);
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
    
    public void printRange(final int lowerBound, final int upperBound)
    {
        int i = java.util.Arrays.binarySearch(elems, lowerBound);
        if (i < 0) i = ~i;
        
        int j = java.util.Arrays.binarySearch(elems, i, elems.length,
                                              upperBound);
        j = (j < 0 ? ~j : j + 1);
        
        while (i != j) System.out.format("%d ", elems[i++]);
        System.out.println();
    }
}

final class Solution {
    public static void main(final String[] args)
    {
        final Primes primes = new Primes(100000000);
        
        try (final java.util.Scanner sc
                = new java.util.Scanner(System.in).useDelimiter("[\\s-]+")) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int lowerBound = sc.nextInt(), upperBound = sc.nextInt();
                primes.printRange(lowerBound, upperBound);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
