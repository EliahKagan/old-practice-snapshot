// sieve2-bench.java - simpler version of sieve2.java, for benchmarking

import java.util.BitSet;
import java.util.stream.IntStream;

final class Arith {
    static int[] primesTo(final int n)
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
        
        return IntStream.concat(IntStream.of(2),
                bits.stream().skip(1L).map(i -> i * 2 + 1)).toArray();
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class UnitTest {
    private static final int DEFAULT_MAX = 10_000_000;
    
    public static void main(final String[] args)
    {
        final int max = (args.length == 0 ? DEFAULT_MAX
                                          : Integer.parseInt(args[0]));
        
        System.out.format("Computing primes to %d ...%n", max);
        
        final int[] primes = Arith.primesTo(max);
        
        System.out.format("... done. Highest prime found was %d.%n",
                          primes[primes.length - 1]);
    }
    
    private UnitTest() { } // the UnitTest class should not be instantiated
}
