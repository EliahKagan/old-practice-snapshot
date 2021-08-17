using System;
using System.Linq;
using System.Numerics;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static int GetValue() => int.Parse(Console.ReadLine());
    
    private static int DigitSum(BigInteger n)
            => n.ToString("R").Sum(c => c - '0');
    
    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, GetValue()))
            Console.WriteLine(DigitSum(BigInteger.One << GetValue()));
    }
}
