<Query Kind="Program" />

private static IEnumerable<int> Sieve(int n)
{
    var a = new bool[n + 1]; // false means not marked as composite
    
    var imax = Convert.ToInt32(Math.Floor(Math.Sqrt(n)));
    for (var i = 3; i <= imax; i += 2) {
        if (!a[i]) {
            var jstep = i * 2;
            for (var j = i * i; j <= n; j += jstep) a[j] = true;
        }
    }
    
    yield return 2;
    for (var k = 3; k <= n; k += 2)
        if (!a[k]) yield return k;
}

private static void Main()
{
    Sieve(37).Dump();
}