<Query Kind="Program">
  <Reference>&lt;RuntimeDirectory&gt;\System.Numerics.dll</Reference>
  <Namespace>System.Numerics</Namespace>
</Query>

private const long M = 10000000000L;

private static long Pow(long b, int e)
{
    if (e < 2) return e == 0 ? 1 : b;
    
    var r = Pow(b, e / 2);
    r *= r;
    if (e % 2 != 0) r *= b;
    
    return r % M;
}

private static long ComputeSelfPowerSum(int n) // need n >= 1
{
    var sum = 1L;
    
    for (; n != 1L; --n)
        if (n % 10 != 0) sum += (long)Pow(n, n);
    
    return sum % M;
}

private static void Main()
{
    const int n = 2000000;
    ComputeSelfPowerSum(n).Dump();
    //Pow(2, 128).Dump();
}