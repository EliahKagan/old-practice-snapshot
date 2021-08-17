import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.IntStream;
import java.util.stream.Stream;

final class Arith {
    // Casting from double extracts square roots accurately from small ints.
    static int sqrt(final int n)
    {
        return (int)Math.sqrt(n);
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class Term {
    public final int base, exponent;
    
    public Term(final int base, final int exponent)
    {
        this.base = base;
        this.exponent = exponent;
    }
}

final class Primes {
    public Primes(final int n)
    {
        elems = sieve(n).toArray();
    }
    
    public boolean isSumOfTwoSquares(final int n)
    {        
        // Uses the sum of two squares theorem:
        // https://en.wikipedia.org/wiki/Sum_of_two_squares_theorem
        final Stream<Term> terms = factorize(n).stream();
        return terms.noneMatch(t -> t.base % 4 == 3 && t.exponent % 2 != 0);
    }
    
    private static IntStream rangeClosed(   // helper method for sieve()
            final int startInclusive, final int endInclusive, final int step)
    {
        return IntStream.rangeClosed(0, (endInclusive - startInclusive) / step)
                        .map(k -> startInclusive + k * step);
    }
    
    private static boolean[] rawSieve(final int n) // helper method for sieve()
    {
        final boolean[] a = new boolean[n + 1];
        
        final int imax = Arith.sqrt(n);
        for (int i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                final int jstep = i * 2;
                for (int j = i * i; j <= n; j += jstep) a[j] = true;
            }
        }
        
        return a;
    }
    
    private static IntStream sieve(final int n) // streams primes to n
    {
        final boolean[] a = rawSieve(n);
        
        return IntStream.concat(IntStream.of(2),
                                rangeClosed(3, n, 2).filter(k -> !a[k]));
    }
    
    private final int[] elems;
    
    private List<Term> factorize(int n)
    {
        final List<Term> terms = new ArrayList<>();
        if (n < 2) return terms;
        
        for (final int p : elems) {
            if (p * p > n) break;
            
            if (n % p == 0) {
                int i = 0;
                
                do ++i;
                while ((n /= p) % p == 0);
                
                terms.add(new Term(p, i));
            }
        }
        
        if (n != 1) terms.add(new Term(n, 1)); // single factor >sqrt(orig. n)
        return terms;
    }
}

final class Solution {
    public static void main(final String[] args)
    {
        final int NMAX = 1_000_000;
        final Primes primes = new Primes(Arith.sqrt(NMAX));
        
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int n = sc.nextInt();
                System.out.println(primes.isSumOfTwoSquares(n) ? "1" : "0");
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
