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
    
    static int[] chainLengths(final int max_seed)
    {
        final int[] lengths = new int[max_seed + 1];
        lengths[1] = 1;
        emitChainLengths(lengths, max_seed);
        return lengths;
    }
    
    static int[] optimalSeeds(final int[] lengths)
    {
        final int[] optima = new int[lengths.length];
        int best_seed = optima[1] = 1, best_length = 1;
        
        for (int seed = 2; seed != optima.length; ++seed) {
            if (best_length <= lengths[seed]) {
                best_length = lengths[seed];
                best_seed = seed;
            }
            
            optima[seed] = best_seed;
        }
        
        return optima;
    }
    
    private Collatz() { } // the Collatz class should not be instantiated
}

final class Solution {
    public static void main(final String[] args)
    {
        final int max_seed = 5000000;
        
        final int[] lengths = Collatz.chainLengths(max_seed);
        final int[] optima = Collatz.optimalSeeds(lengths);
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(optima[sc.nextInt()]);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
