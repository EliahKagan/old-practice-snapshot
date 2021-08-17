using System;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var a = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
        Array.Sort(a);
        
        var acc = 0L;
        for (var k = 1L; --n >= 0; k <<= 1) acc += a[n] * k;
        Console.WriteLine(acc);
    }
}
