import java.io.InputStream;
import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.IntStream;

final class Pair {
    public final int left, right;
    
    public Pair(final int left, final int right)
    {
        this.left = left;
        this.right = right;
    }
    
    public Pair(final Scanner sc)
    {
        this.left = sc.nextInt();
        this.right = sc.nextInt();
    }
    
    public int count()
    {
        return right - left + 1;
    }
}

final class Pairs { // static methods for collections of Pair objects
    public static void fill(final Pair[] pairs, final Scanner sc)
    {
        for (int i = 0; i != pairs.length; ++i) pairs[i] = new Pair(sc);
    }
    
    public static Pair[] read(final Scanner sc, final int length)
    {
        final Pair[] pairs = new Pair[length];
        fill(pairs, sc);
        return pairs;
    }
    
    public static Pair[] read(final InputStream in)
    {
        try (final Scanner sc = new Scanner(in)) {
            return read(sc, sc.nextInt());
        }
    }
    
    public static Pair minLeftMaxRight(final Pair[] pairs)
    {
        int min = Integer.MAX_VALUE, max = Integer.MIN_VALUE;
        
        for (final Pair p : pairs) {
            if (min > p.left) min = p.left;
            if (max < p.right) max = p.right;
        }
        
        return new Pair(min, max);
    }
    
    private Pairs() { } // the Pairs class should not be instantiated
}

final class Searcher {
    private final int[] array;
    private final int fromIndex, toIndex;
    
    // Creates a searcher between indices low and high (inclusive) for seq,
    // assumed strictly increasing (i.e., sorted and unique) in this range.
    public Searcher(final int[] seq, final int low, final int high)
    {
        array = seq;
        fromIndex = low;
        toIndex = high + 1;
    }
    
    public Searcher(final int[] seq, final int low)
    {
        this(seq, low, seq.length - 1);
    }
    
    public Searcher(final int[] seq)
    {
        this(seq, 0);
    }
    
    public int minGreaterOrEqual(final int key) // returns index, not value
    {
        final int i = binarySearch(key);
        return i < 0 ? ~i : i;
    }
    
    public int maxLessOrEqual(final int key) // returns index, not value
    {
        final int i = binarySearch(key);
        return i < 0 ? ~i - 1 : i;
    }
    
    public Pair range(final int min, final int max) // returns pair of indices
    {
        return new Pair(minGreaterOrEqual(min), maxLessOrEqual(max));
    }
    
    public Pair range(final Pair bounds) // returns pair of indices
    {
        return range(bounds.left, bounds.right);
    }
    
    private int binarySearch(final int key)
    {
        return Arrays.binarySearch(array, fromIndex, toIndex, key);
    }
}

final class Searchers { // static utility methods relating to Searcher objects
    public static Searcher getLeftSearcher(int[] seq, int max)
    {
        final int high = new Searcher(seq).maxLessOrEqual(max);
        return new Searcher(seq, 0, high);
    }
    
    public static Searcher getRightSearcher(int[] seq, int min)
    {
        final int low = new Searcher(seq).minGreaterOrEqual(min);
        return new Searcher(seq, low, seq.length - 1);
    }
    
    private Searchers() { } // the Searchers class should not be instantiated
}

final class Primes {
    private static int sqrt32(final int n)
    {
        return (int)Math.round(Math.floor(Math.sqrt(n)));
    }
    
    private static IntStream rangeClosed(
            final int startInclusive, final int endInclusive, final int step)
    {
        return IntStream.rangeClosed(0, (endInclusive - startInclusive) / step)
                        .map(k -> startInclusive + k * step);
    }
    
    private static IntStream sieve(final int n) // streams primes up to n
    {
        final boolean[] a = new boolean[n + 1];
        
        final int imax = sqrt32(n);
        for (int i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                final int jstep = i * 2;
                for (int j = i * i; j <= n; j += jstep) a[j] = true;
            }
        }
        
        return IntStream.concat(IntStream.of(2),
                                rangeClosed(3, n, 2).filter(k -> !a[k]));
    }
    
    static int[] to(final int n) // returns array of all primes <= max(n, 2)
    {
        return sieve(n).toArray();
    }
    
    private Primes() { } // the Primes class should not be instantiated
}

final class Solution {
    public static void main(final String[] args)
    {
        final Pair[] pairs = Pairs.read(System.in);
        final Pair bounds = Pairs.minLeftMaxRight(pairs);
        
        final int[] primes = Primes.to(bounds.right);
        final Searcher s = Searchers.getRightSearcher(primes, bounds.left);
        
        for (final Pair p : pairs) {
            final int prime_count = s.range(p).count();
            int composite_count = p.count() - prime_count;
            if (p.left == 1) --composite_count;
            
            System.out.println(composite_count - prime_count);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
