<Query Kind="Program" />

private static bool IsPrime(int n)
{
    if (n < 2) return false;
    
    var r = Convert.ToInt32(Math.Floor(Math.Sqrt(n)));
    
    for (var i = 2; i <= r; ++i)
        if (n % i == 0) return false;
    
    return true;
}

private static void Main()
{
    var two_billion = 2000000000;
    Enumerable.Range(two_billion - 10000, 10000).Count(IsPrime).Dump();
}
