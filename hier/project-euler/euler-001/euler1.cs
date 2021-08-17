// euler1.cs - Project Euler problem 1: Multiples of 3 and 5

using System;
using System.Linq;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Program {
    private static void Main()
    {
        var n = 0;

        foreach (var k in Enumerable.Range(0, 1000))
            if (k % 3 == 0 || k % 5 == 0) n += k;

        Console.WriteLine(n);
    }
}
