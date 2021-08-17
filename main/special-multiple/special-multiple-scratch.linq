<Query Kind="Program" />

private static IEnumerable<long> SpecialNumbers()
{
    long x;
    var bits = 1L;
    while (long.TryParse(Convert.ToString(bits++, 2).Replace('1', '9'), out x))
        yield return x;
}

private static void Main()
{
    var a = SpecialNumbers().ToArray();
    Enumerable.Range(1, 500).Select(n => a.First(x => x % n == 0)).Max().Dump();
    
    //Enumerable.Range(1, 500).All(n => a.Any(x => x % n == 0)).Dump();
}