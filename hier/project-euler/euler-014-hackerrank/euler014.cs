using static System.Console;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Collatz {
    private static void EmitChainLengths(int[] lengths, long max_seed)
    {
        for (var seed = 2L; seed <= max_seed; ++seed) {
            if (lengths[seed] != 0) continue;
    
            // trace chain to count hops
            var hops = 1;
            for (var i = seed; ; ++hops) {
                i = (i % 2L == 0L ? i / 2L : i * 3L + 1L);
        
                if (i <= max_seed && lengths[i] != 0) {
                    hops += lengths[i];
                    break;
                }
            }
    
            // retrace chain, marking lengths from hops count
            lengths[seed] = hops--;
            for (var i = seed; ; --hops) {
                i = (i % 2L == 0L ? i / 2L : i * 3L + 1L);
        
                if (i <= max_seed) {
                    if (lengths[i] != 0) break;
                    lengths[i] = hops;
                }
            }
        }
    }

    internal static int[] ChainLengths(long max_seed)
    {
        var lengths = new int[max_seed + 1L];
        lengths[1L] = 1;
        EmitChainLengths(lengths, max_seed);
        return lengths;
    }

    internal static int[] OptimalSeeds(this int[] lengths)
    {
        var optima = new int[lengths.Length];
        var best_seed = optima[1] = 1;
        var best_length = 1;

        for (var seed = 2; seed != optima.Length; ++seed) {
            if (best_length <= lengths[seed]) {
                best_length = lengths[seed];
                best_seed = seed;
            }
    
            optima[seed] = best_seed;
        }

        return optima;
    }
}

internal static class Solution {
    private static int Get() => int.Parse(ReadLine());

    private static void Main()
    {
        const long max_seed = 5000000L;
        var optima = Collatz.ChainLengths(max_seed).OptimalSeeds();
        for (var t = Get(); t > 0; --t) WriteLine(optima[Get()]);
    }
}
