<Query Kind="Program" />

private static int Get() => int.Parse(Console.ReadLine());

private static int[] Fibonacci(int n, int m)
{
    var a = new int[n + 1];
    
    a[0] = 1;
    a[1] = 1;
    
    for (var i = 2; i <= n; ++i) a[i] = (a[i - 2] + a[i - 1]) % m;
    
    return a;
}

private static void Main()
{
    var a = Fibonacci(100, 1000000007);
    
    Enumerable.Range(0, a.Length)
              .Zip(a, (Index, Elem) => new { Index, Elem })
              .Dump();
}