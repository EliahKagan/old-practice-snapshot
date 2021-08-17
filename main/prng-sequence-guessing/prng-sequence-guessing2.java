import java.util.*;

final class Solution {
    private static final int BOUND = 1000, SAMPLE_COUNT = 10, EXTRA_COUNT = 10;
    
    // Reads input data into array of sample PRNG output values.
    private static int[] readSamples(final Scanner sc)
    {
        final int[] samples = new int [SAMPLE_COUNT];
        for (int i = 0; i != samples.length; ++i) samples[i] = sc.nextInt();
        return samples;
    }
    
    // Test a single PRNG to check if it produces all the specified samples.
    private static boolean test(final Random gen, final int[] samples)
    {
        for (final int s : samples)
            if (gen.nextInt(BOUND) != s) return false;
        
        return true;
    }
    
    // Outputs report of seed and subsequent values.
    private static void report(final long seed, final Random gen)
    {
        System.out.print(seed);
        
        for (int i = EXTRA_COUNT; i != 0; --i)
            System.out.format(" %d", gen.nextInt(BOUND));
        
        System.out.println();
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int n = sc.nextInt(); n > 0; --n) {
                long seed = sc.nextLong();
                final long max_seed = sc.nextLong();
                final int[] samples = readSamples(sc);
                
                for (; seed <= max_seed; ++seed) {
                    final Random gen = new Random(seed);
                    
                    if (test(gen, samples)) {
                        report(seed, gen);
                        break;
                    }
                }
                
                if (seed > max_seed) { // tried all seeds unsuccessfully
                    System.out.println(
                            "ERROR: No generator found with those values.");
                }
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
