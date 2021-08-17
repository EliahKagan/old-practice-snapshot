using System;
using System.Linq;

internal static class Program {
    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine())))
            Console.WriteLine(int.Parse(Console.ReadLine()) + 1);
    }
}
