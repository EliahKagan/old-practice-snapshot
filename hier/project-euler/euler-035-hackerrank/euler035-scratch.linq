<Query Kind="Program" />

internal static class CircularPrimes {
    private const int Base = 10;
    
    internal const int DefaultN = 1000000;
    
    private static IEnumerable<int> ToDigits(this int k)
    {
        do yield return k % Base;
        while ((k /= Base) != 0);
    }
    
    private static IEnumerable<int> GeneralRotations(int val)
    {
        var digits = val.ToDigits().ToArray();
        var len = digits.Length;
        
        for (var i = 0; 1 != len; ++i) {
            var ret = digits[i];
            var mul = 1;
            for (var j = i; ++j != len; ) ret += digits[j] * (mul *= Base);
            for (var j = 0; j != i; ++j) ret += digits[j] * (mul *= Base);
            yield return ret;
        }
    }
    
    private static IEnumerable<int> Rotations(int val)
    {
        var digits = val.ToDigits().ToArray();
        if (digits.Contains(0)) yield break;
        yield return val;
        
        var len = digits.Length;
        for (var i = 1; i != len; ++i) {
            var ret = digits[i];
            var mul = 1;
            for (var j = i; ++j != len; ) ret += digits[j] * (mul *= Base);
            ret += digits[0] * (mul *= Base);
            for (var j = 0; ++j != i; ) ret += digits[j] * (mul *= Base);
            yield return ret;
        }
    }
    
    private static int MinRotation(int val)
            => Rotations(val).DefaultIfEmpty(-1).Min();
    
    private static void Main()
    {
        Enumerable.Range(0, DefaultN).Select(MinRotation).Dump();
    }
}