final class Algo {
    static void runningMaxInPlace(final int[] seq)
    {
        int floor = Integer.MIN_VALUE;
        
        for (int i = 0; i != seq.length; ++i) {
            if (floor < seq[i]) floor = seq[i];
            else seq[i] = floor;
        }
    }
    
    private Algo() { } // the Algo class should not be instantiated
}

final class Collatz {
    private static void emitChainLengths(final int[] lengths,
                                         final int max_seed)
    {
        for (int seed = 2; seed <= max_seed; ++seed) {
            if (lengths[seed] != 0) continue;
            
            // trace chain to count hops
            int hops = 1;
            for (long i = seed; ; ++hops) {
                i = (i % 2L == 0L ? i / 2L : i * 3L + 1L);
                
                if (i <= max_seed && lengths[(int)i] != 0) {
                    hops += lengths[(int)i];
                    break;
                }
            }
            
            // retrace chain, marking lengths from hops count
            lengths[seed] = hops--;
            for (long i = seed; ; --hops) {
                i = (i % 2L == 0L ? i / 2L : i * 3L + 1L);
                
                if (i <= max_seed) {
                    if (lengths[(int)i] != 0) break;
                    lengths[(int)i] = hops;
                }
            }
        }
    }
    
    private static int[] chainLengths(final int max_seed)
    {
        final int[] lengths = new int[max_seed + 1];
        lengths[1] = 1;
        emitChainLengths(lengths, max_seed);
        return lengths;
    }
    
    // bestLengths(max_seed)[n] is the length of the longest Collatz chain
    // whose seed lies between 1 and n, inclusive (requires n <= max_seed).
    static int[] bestLengths(final int max_seed)
    {
        final int[] lengths = chainLengths(max_seed);
        Algo.runningMaxInPlace(lengths);
        return lengths;
    }
    
    private Collatz() { } // the Collatz class should not be instantiated
}

final class Solution {
    public static void main(final String[] args)
    {
        final int max_seed = 1000000;
        
        final int[] ans = Collatz.bestLengths(max_seed);
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(ans[sc.nextInt()]);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
