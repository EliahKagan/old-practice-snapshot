using System;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Program {
    private static int[] GetRecord()
            => Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

    private static void Main()
    {
        var d = GetRecord()[1];
        var a = GetRecord();
        Console.WriteLine(string.Join(" ", a.Skip(d).Concat(a.Take(d))));
    }
}
