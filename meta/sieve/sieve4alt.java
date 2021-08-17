// sieve4.java - compact Sieve of Eratosthenes (decreased memory footprint)
// This version avoids unnecessary bitset writes, traverses the bitset only
// once, and doesn't use streams. (But it seems to be slower than sieve4.java.)

final class Arith {
    static int sqrt32(final int n)
    {
        return (int)Math.round(Math.floor(Math.sqrt(n)));
    }
    
    static int overestimate_pi_fn(final int n)
    {
        // See https://projecteuclid.org/download/pdf_1/euclid.ijm/1255631807,
        // Theorem 2, Corollary 1, equation 3.6.
        final double x = n;
        return (int)Math.round(Math.ceil(x * 1.25506 / Math.log(x)));
    }
    
    // Places the primes <= n into dest. Returns the count of primes found.
    static int sieve(final int n, final long[] dest)
    {
        final int len = (n + 1) / 2;
        final java.util.BitSet bits = new java.util.BitSet(len);
        
        dest[0] = 2L;
        int k = 1;
        
        final int istop = sqrt32(n) / 2 + 1;
        for (int i = 1; i != istop; ++i) {
            if (!bits.get(i)) {
                final int p = i * 2 + 1;
                dest[k++] = p;
                for (int j = (i + 1) * i * 2; j < len; j += p) bits.set(j);
            }
        }
        
        for (int i = istop; i != len; ++i)
            if (!bits.get(i)) dest[k++] = i * 2 + 1;
        
        return k;
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
            
            final long[] primes = new long[HIGH_COUNT];
            final int count = Arith.sieve(HIGH_MAX, primes);
            
            System.out.println(" Done!");
            System.out.format("%d was the highest of %d primes found.%n",
                              primes[count - 1], count);
        } else {
            final int max = (args.length == 0 ? DEFAULT_MAX
                                              : Integer.parseInt(args[0]));
            
            System.out.format("Primes <= %d: ", max);
            
            final long[] primes = new long[Arith.overestimate_pi_fn(max)];
            final int count = Arith.sieve(max, primes);
            
            for (int i = 0; i != count; ++i)
                System.out.format(" %d", primes[i]);
            
            System.out.println();
        }
    }
    
    private UnitTest() { } // the UnitTest class should not be instantiated
}
