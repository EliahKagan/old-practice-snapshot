import java.util.Random;

// Like Random, but knows and will tell you its seed.
class IdRandom extends Random {
    public final long seed;
    
    public IdRandom(final long seed)
    {
        super(seed);
        this.seed = seed;
    }
}

final class Program {
    private static final int COUNT = 10, BOUND = 1000;
    
    public static void main(final String[] args)
    {
        final IdRandom r = new IdRandom(Integer.parseInt(args[0]));
        
        for (int i = 0; i != COUNT; ++i)
            System.out.format("%d: %d%n", i, r.nextInt(BOUND));
        
        System.out.format("%nSeed: %d%n", r.seed);
    }
    
    private Program() { } // the Program class should not be instantiated
}
