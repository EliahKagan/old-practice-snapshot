using System;
using System.Globalization;
using System.Linq;

internal static class Solution {
    private static int Rotate(int n)
    {
        return (n + 1) % 10;
    }

    private static string Rotate(string ch)
    {
        return Rotate(int.Parse(ch, CultureInfo.InvariantCulture))
                .ToString(CultureInfo.InvariantCulture);
    }

    private static void Main()
    {
        var s = Console.ReadLine();

        foreach (var i in Enumerable.Range(0, s.Length))
            Console.Write(Rotate(s.Substring(i, 1)));

        Console.WriteLine();
    }
}
