using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class ListEx {
    private static int LowerBound(this List<int> arr, int key,
                                   int low, int high)
    {
        if (high < low) return low;
        
        var mid = low + (high - low) / 2;
        
        return arr[mid] < key ? arr.LowerBound(key, mid + 1, high)
                              : arr.LowerBound(key, low, mid - 1);
    }
    
    internal static int LowerBound(this List<int> arr, int key)
            => arr.LowerBound(key, 0, arr.Count - 1);
}

internal static class Arith {
    private static IEnumerable<BigInteger> Fibonacci()
    {
        var a = BigInteger.Zero;
        var b = BigInteger.One;
        
        yield return a;
        
        for (; ; ) {
            yield return b;
            
            var tmp = a;
            a = b;
            b += tmp;
        }
    }
    
    private static int Length(BigInteger n) => n.ToString("R").Length;
    
    internal static List<int> FibonacciLengths(this int max)
            => new List<int>(Fibonacci().Select(Length)
                                        .TakeWhile(len => len <= max));
}

internal static class Solution {
    private static int ReadValue() => int.Parse(Console.ReadLine());

    private static List<int> ReadAllValues()
    {
        var t = ReadValue();
        var values = new List<int>(t);
        while (t-- > 0) values.Add(ReadValue());
        return values;
    }
    
    private static void Main()
    {
        var values = ReadAllValues();
        var lengths = values.Max().FibonacciLengths();
        
        values.ForEach(n => Console.WriteLine(lengths.LowerBound(n)));
    }
}
