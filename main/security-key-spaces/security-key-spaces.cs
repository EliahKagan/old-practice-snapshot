using System;
using System.Globalization;
using System.Linq;

internal static class Solution {
    private static int Rotate(int n, int e)
    {
        return (n + e) % 10;
    }

    private static string Rotate(string ch, int e)
    {
        return Rotate(int.Parse(ch, CultureInfo.InvariantCulture), e)
                .ToString(CultureInfo.InvariantCulture);
    }

    private static void Main()
    {
        var s = Console.ReadLine();
        var e = int.Parse(Console.ReadLine());

        foreach (var i in Enumerable.Range(0, s.Length))
            Console.Write(Rotate(s.Substring(i, 1), e));

        Console.WriteLine();
    }
}
