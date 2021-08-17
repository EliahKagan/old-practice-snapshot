import java.util.*;

// Like Random, but knows and will tell you its seed.
class IdRandom extends Random {
    public final long seed;
    
    public IdRandom(final long seed)
    {
        super(seed);
        this.seed = seed;
    }
}

final class Solution {
    private static final int BOUND = 1000, SAMPLE_COUNT = 10, EXTRA_COUNT = 10;
    
    // Creates a collection of generators for all seeds in the specified range.
    private static ArrayList<IdRandom> getGens(long min_seed,
                                               final long max_seed)
    {
        final long size = max_seed - min_seed + 1L;
        if (size <= 0L) return new ArrayList<>(0);
        if (size > Integer.MAX_VALUE)
            throw new IllegalArgumentException("range of seeds way too big");
        
        final ArrayList<IdRandom> gens = new ArrayList<>((int)size);
        while (min_seed <= max_seed) gens.add(new IdRandom(min_seed++));
        return gens;
    }
    
    // Builds a new collection of just those generators whose next output was
    // equal to the provided sample value.
    private static ArrayList<IdRandom> filterGens(
            final ArrayList<IdRandom> gens, final int sample)
    {
        ArrayList<IdRandom> passing_gens = new ArrayList<>(gens.size());
        
        for (final IdRandom r : gens)
            if (r.nextInt(BOUND) == sample) passing_gens.add(r);
        
        return passing_gens;
    }
    
    // Finds the unique generator consistent with the samples provided. If
    // there is no such generator, returns null.
    private static IdRandom identifyGen(ArrayList<IdRandom> gens,
                                        final int[] samples)
    {
        for (final int s : samples) gens = filterGens(gens, s);
        return gens.size() == 1 ? gens.get(0) : null;
    }
    
    // Output report of seed and subsequent values. For an error message
    // indicating no suitable generator was found, pass null as gen parameter.
    private static void report(final IdRandom gen)
    {
        if (gen == null) {
            System.out.println("ERROR: No generator found with those values.");
            return;
        }
        
        System.out.print(gen.seed);
        
        for (int i = EXTRA_COUNT; i != 0; --i)
            System.out.format(" %d", gen.nextInt(BOUND));
        
        System.out.println();
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int n = sc.nextInt(); n > 0; --n) {
                final int min_seed = sc.nextInt(), max_seed = sc.nextInt();
                
                final int[] samples = new int[SAMPLE_COUNT];
                for (int i = 0; i != samples.length; ++i)
                    samples[i] = sc.nextInt();
                
                report(identifyGen(getGens(min_seed, max_seed), samples));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
