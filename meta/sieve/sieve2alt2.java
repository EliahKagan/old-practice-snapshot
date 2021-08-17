// sieve2alt.java - compact Sieve of Eratosthenes (decreased memory footprint)
//      This version is further modified to avoid unnecessary bitset writes.

import java.util.BitSet;

final class Arith {
    static int sqrt32(final int n)
    {
        return (int)Math.round(Math.floor(Math.sqrt(n)));
    }
    
    private static BitSet rawSieve(final int n) // finds primes to n
    {
        final int len = (n + 1) / 2;
        final BitSet bits = new BitSet(len);
        
        final int istop = sqrt32(n) / 2 + 1;
        for (int i = 1; i != istop; ++i) {
            if (!bits.get(i)) {
                final int jstep = i * 2 + 1;
                for (int j = (i + 1) * i * 2; j < len; j += jstep)
                    bits.set(j);
            }
        }
        
        return bits;
    }
    
    static long[] sieve(final int n, long[] dest) // puts primes to n into dest
    {
        final BitSet bits = rawSieve(n);
        if (dest == null) dest = new long[bits.cardinality()];
        
        dest[0] = 2L;
        
        final int stop = (n + 1) / 2;
        for (int j = 1, i = 0; (i = bits.nextClearBit(++i)) != stop; ++j)
            dest[j] = i * 2 + 1;
        
        return dest;
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class UnitTest {
    private static final int DEFAULT_MAX = 100;
    private static final int HIGH_MAX = 1_000_000_000;
    private static final int HIGH_COUNT = 50_847_534;
    
    public static void main(final String[] args)
    {
        if (args.length == 1 && args[0].trim().equals("-")) {
            System.out.format("Computing primes <= %d...", HIGH_MAX);
            
            final long[] primes = Arith.sieve(HIGH_MAX, new long[HIGH_COUNT]);
            
            System.out.println(" Done!");
            System.out.format("%d was the highest of %d primes found.%n",
                    primes[primes.length - 1], primes.length);
        } else {
            final int max = (args.length == 0 ? DEFAULT_MAX
                                              : Integer.parseInt(args[0]));
            
            System.out.format("Primes <= %d: ", max);
            
            for (final long n : Arith.sieve(max, null))
                System.out.format(" %d", n);
            
            System.out.println();
        }
    }
    
    private UnitTest() { } // the UnitTest class should not be instantiated
}
