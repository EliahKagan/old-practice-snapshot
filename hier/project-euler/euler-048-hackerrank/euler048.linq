<Query Kind="Program" />

private const long M = 10000000000L;

private static long Pow(long b, long e)
{
    if (e < 2L) return e == 0L ? 1L : b;
    
    var r = Pow(b, e / 2L);
    r *= r;
    if (e % 2L != 0L) r *= b;
    
    return r % M;
}

private static long ComputeSelfPowerSum(long n) // need n >= 1
{
    var sum = 1L;
    
    //for (var i = 2L; i <= n; ++i)
    
    for (; n != 1L; --n)
        /*if (n % 10L != 0L)*/ sum += Pow(n, n);
    
    return sum % M;
}

private static void Main()
{
    //const long n = 2000000;
    //ComputeSelfPowerSum(n).Dump();
    Pow(2, 128).Dump();
}