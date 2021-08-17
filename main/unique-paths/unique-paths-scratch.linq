<Query Kind="Program" />

//#define WITH_DUMP_LOGIC

internal sealed class Binom {
    public Binom(int max) {
        _c = new int[max + 1, max + 1];
        _c[0, 0] = 1;
        
        for (var i = 1; i != max + 1; ++i) {
            _c[i, i] = _c[i, 0] = 1;
            for (var j = 1; j != i; ++j) {
                _c[i, max - j] = _c[i, j] = _c[i - 1, j - 1] + _c[i - 1, j];
                if (_c[i, j] == 0) _c[i, j].Dump($"{i}, {j}");
            }
        }
    }
    
    public int this[int i, int j] => _c[i, j];

#if WITH_DUMP_LOGIC
    private object ToDump() => _c;
#endif

    private readonly int[,] _c; // Pascal's triangle (binomial coefficients)
}

public class Solution {
    private const int mmax = 100, nmax = 100;
    
    private static readonly Binom C = new Binom(mmax + nmax - 2).Dump();
    
    public int UniquePaths(int m, int n) => C[m + n - 2, m - 1];
}

private static void Main() {
    var s = new Solution();
    s.UniquePaths(5, 10).Dump();
    s.UniquePaths(8, 7).Dump();
    s.UniquePaths(1, 1).Dump();
    s.UniquePaths(14, 12).Dump();
    s.UniquePaths(50, 75).Dump();
    s.UniquePaths(100, 100).Dump();
}