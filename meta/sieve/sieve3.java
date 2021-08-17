// sieve3.java - compact Sieve of Eratosthenes (decreased memory footprint)
// This version advances i using bits.nextSetBit() instead of bits.get().
// (Preliminary testing suggests this way is slightly _slower_ than before.)

import java.util.BitSet;
import java.util.stream.IntStream;
import java.util.stream.LongStream;

final class Arith {
    static int sqrt32(final int n)
    {
        return (int)Math.round(Math.floor(Math.sqrt(n)));
    }
    
    private static BitSet rawSieve(final int n) // finds primes to n
    {
        final int len = (n + 1) / 2;
        final BitSet bits = new BitSet(len);
        bits.set(0, len);
        
        final int imax = sqrt32(n) / 2;
        for (int i = bits.nextSetBit(1); i <= imax; i = bits.nextSetBit(++i)) {
            final int jstep = i * 2 + 1;
            for (int j = (i + 1) * i * 2; j < len; j += jstep) bits.clear(j);
        }
        
        return bits;
    }
    
    static LongStream sieve(final int n) // streams primes to n
    {
        final LongStream head = LongStream.of(2L);
        
        final IntStream tail = rawSieve(n).stream()
                                          .skip(1L)
                                          .map(i -> i * 2 + 1);
        
        return LongStream.concat(head, tail.asLongStream());
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class UnitTest {
    private static final int DEFAULT_MAX = 100, HIGH_MAX = 1_000_000_000;
    
    public static void main(final String[] args)
    {
        if (args.length == 1 && args[0].trim().equals("-")) {
            System.out.format("Computing primes <= %d...", HIGH_MAX);
            
            final long[] primes = Arith.sieve(HIGH_MAX).toArray();
            
            System.out.println(" Done!");
            System.out.format("%d was the highest of %d primes found.%n",
                    primes[primes.length - 1], primes.length);
        } else {
            final int max = (args.length == 0 ? DEFAULT_MAX
                                              : Integer.parseInt(args[0]));

            System.out.format("Primes <= %d: ", max);
            Arith.sieve(max).forEachOrdered(n -> System.out.format(" %d", n));
            System.out.println();
        }
    }
    
    private UnitTest() { } // the UnitTest class should not be instantiated
}
