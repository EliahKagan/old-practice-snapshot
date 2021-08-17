// mutable.cs - multiplication table generator

using System;
using System.Linq;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class MulTable {
    const int Max = 12;

    private static void Put<T>(T x)
    {
        Console.Write("{0,4}", x);
    }

    private static void Main()
    {
        var twice = Enumerable.Range(0, 2);
        var range = Enumerable.Range(0, Max + 1);

        // leading row, consisting of labels
        foreach (var i in twice) Put("");
        foreach (var i in range) Put(i);
        foreach (var i in twice) Console.WriteLine();
        
        // subsequent rows, label followed by products
        foreach (var i in range) {
            Put(i);
            Put("");
            foreach (var j in range) Put(i * j);
            Console.WriteLine();
        }
    }
}
