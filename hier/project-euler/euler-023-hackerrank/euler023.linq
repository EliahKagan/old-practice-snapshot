<Query Kind="Program" />

internal static class Solution {
    private static int SumProperDivisors(int n)
    {
        if (n < 3) return n - 1;
    
        var stop = (int)Math.Sqrt(n);
        var sum = 1;
        
        if (stop * stop == n) sum += stop;
        else ++stop;
    
        for (var i = 2; i != stop; ++i)
            if (n % i == 0) sum += i + n / i;
    
        return sum;
    }
    
    private static int[] GetAbundantNumbers(int max)
            => Enumerable.Range(1, max)
                         .Where(i => SumProperDivisors(i) > i)
                         .ToArray();
    
    private static int Get() => int.Parse(Console.ReadLine());
    
    private static bool HasPairWithSum(this int[] a, int n)
    {
        var len = a.Length;
        
        for (var i = 0; i != len; ++i) {
            var key = n - a[i];
            if (key < a[i]) break;
            
            if (Array.BinarySearch(a, i, len - i, key) >= 0)
                return true;
        }
        
        return false;
    }
    
    private static void Main()
    {
        var ns = Enumerable.Range(0, Get()).Select(i => Get()).ToArray();
        var a = GetAbundantNumbers(ns.Max());
        
        foreach (var n in ns)
            Console.WriteLine(a.HasPairWithSum(n) ? "YES" : "NO");
    }
}