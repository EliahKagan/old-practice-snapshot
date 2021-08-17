import java.util.Map;
import java.util.stream.IntStream;

final class Arith {
    // Casting from double extracts square roots accurately from small ints.
    static int sqrt(final int n)
    {
        return (int)Math.sqrt(n);
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class Combo {
    public final int length;
    public final int[] cycles, orders;
    
    public Combo(final int[] cycles, final int[] orders)
    {
        this.length = Math.min(cycles.length, orders.length);
        this.cycles = cycles;
        this.orders = orders;
    }
    
    public boolean Advance()
    {
        int i = 0;
        while (i != length && cycles[i] == orders[i]) ++i;
        if (i == length) return false;
        
        for (int j = 0; j != i; ++j) cycles[j] = 0;
        ++cycles[i];
        return true;
    }
}

final class Factorization {
    private class DivisorSupplier implements java.util.function.IntSupplier {
        private final int[] divisor_exponents = new int[exponents.length];
        
        private final Combo combo = new Combo(divisor_exponents, exponents);
        
        private boolean done = false;
        
        @Override
        public int getAsInt()
        {
            if (done) throw new IllegalStateException();
            final int divisor = new Factorization(primes, divisor_exponents)
                                        .getValue();
            done = !combo.Advance();
            return divisor;
        }
    }
    
    private final int[] primes, exponents;
    
    // Constructs a Factorization object from primes and exponents arrays.
    // This is a Factorization _view_ of the arrays; they aren't cloned/copied.
    private Factorization(final int[] primes, final int[] exponents)
    {
        this.primes = primes;
        this.exponents = exponents;
    }
    
    // Constructs a Factorization object from a (prime factor)->(exponent) map.
    Factorization(final Map<Integer, Integer> powers)
    {
        primes = new int[powers.size()];
        int i = 0;
        for (final int key : powers.keySet()) primes[i++] = key;
        java.util.Arrays.sort(primes);
        
        exponents = new int[i];
        for (int j = 0; j != i; ++j) exponents[j] = powers.get(primes[j]);
    }
    
    public int getValue() // Computes the number that has this factorization.
    {
        int value = 1;
        
        for (int i = 0; i != primes.length; ++i)
            for (int e = exponents[i]; e != 0; --e) value *= primes[i];
        
        return value;
    }
    
    // Computes (efficiently, not really by counting) the total number of
    // distinct integer divisors of the number that has this factorization.
    public int countDivisors()
    {
        int count = 1;
        for (final int e : exponents) count *= e + 1;
        return count;
    }
    
    // Returns a stream of all the integer divisors of the number that has this
    // factorization, in strictly increasing order.
    public IntStream getDivisors()
    {
        return IntStream.generate(new DivisorSupplier())
                        .limit(countDivisors());
    }
}

final class Primes {
    private static IntStream rangeClosed(   // helper method for sieve()
            final int startInclusive, final int endInclusive, final int step)
    {
        return IntStream.rangeClosed(0, (endInclusive - startInclusive) / step)
                        .map(k -> startInclusive + k * step);
    }
    
    private static IntStream sieve(final int n) // streams primes up to n
    {
        final boolean[] a = new boolean[n + 1];
        
        final int imax = Arith.sqrt(n);
        for (int i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                final int jstep = i * 2;
                for (int j = i * i; j <= n; j += jstep) a[j] = true;
            }
        }
        
        return IntStream.concat(IntStream.of(2),
                                rangeClosed(3, n, 2).filter(k -> !a[k]));
    }
    
    private final int[] elems;
    
    public Primes(final int n)
    {
        elems = sieve(n).toArray();
    }
    
    public IntStream stream()
    {
        return IntStream.of(elems);
    }
    
    // Helper method for getFactorMap(). Puts an odd n's remaining factor-power
    // entries in factor_map. See getFactorMap() for further details.
    private void putOddFactorEntries(final Map<Integer, Integer> factor_map,
                                     int n)
    {
        final int sqrt = Arith.sqrt(n);
        for (int i = 1; i != elems.length && elems[i] <= sqrt; ++i) {
            if (n % elems[i] == 0) {
                int count = 1;
                while ((n /= elems[i]) % elems[i] == 0) ++count;
                factor_map.put(elems[i], count);
                
                if (n == 1) return;
            }
        }
        
        // what remains (since n != 1 here) is a single prime factor > sqrt
        factor_map.put(n, 1);
    }
    
    // For a prime p such that the current Primes object has all the primes up
    // to sqrt(p), getFactorMap(n).get(p) is the number of factors of p that
    // may be extracted from n by division (n > 0).
    private Map<Integer, Integer> getFactorMap(int n)
    {
        int twos = 0; // we will quickly pull out all factors of 2
        for (; (n & 1) == 0; n >>= 1) ++twos;
        
        final Map<Integer, Integer> factor_map = new java.util.HashMap<>();
        if (twos != 0) factor_map.put(2, twos);
        if (n != 1) putOddFactorEntries(factor_map, n);
        return factor_map;
    }
    
    // For an integer n > 0 and a Primes object, primes, containing primes up
    // to sqrt(n) or higher, primes.getFactorization(n) returns a Factorization
    // object with information on which prime factors have nonzero powers in
    // the prime factorization of n, and what those corresponding powers are.
    public Factorization getFactorization(final int n)
    {
        return new Factorization(getFactorMap(n));
    }
    
    // For an integer n > 0 and a Primes object, primes, containing primes up
    // to sqrt(n) or higher, primes.sumProperDivisors(n) computes the sum of
    // all distinct integer divisors of n, not including n itself.
    public int sumProperDivisors(final int n)
    {
        return getFactorization(n).getDivisors().sum() - n;
    }
}

final class Solution {
    private static int[] read_record()
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            return IntStream.range(0, sc.nextInt())
                            .map(i -> sc.nextInt())
                            .toArray();
        }
    }
    
    public static void main(final String[] args)
    {
        final int[] a = read_record();
        final int max = IntStream.of(a).max().getAsInt();
        final Primes primes = new Primes(Arith.sqrt(max));
        
        IntStream.of(a).map(primes::sumProperDivisors)
                       .forEachOrdered(System.out::println);
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
