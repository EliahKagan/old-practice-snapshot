// multable0.cs - generates plain multiplication table (i.e., without labels)

using System;
using System.Linq;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class MulTable {
    private static void Main()
    {
        var range = Enumerable.Range(1, 12);
        foreach (var i in range) {
            foreach (var j in range) Console.Write("{0,4}", i * j);
            Console.WriteLine();
        }
    }
}
