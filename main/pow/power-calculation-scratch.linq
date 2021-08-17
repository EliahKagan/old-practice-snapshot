<Query Kind="Program" />

private const int M = 100;

private static int Pow(int b, long e)
{
    if (e < 2L) return e == 0L ? 1 : b;
    
    var r = Pow(b, e / 2L);
    r *= r;
    if (e % 2L != 0L) r *= b;
    
    return r % M;
}

private static void Main()
{
    const int k = 83294618;
    const long n = 3217894213;
    Pow(k, n).Dump();
}

