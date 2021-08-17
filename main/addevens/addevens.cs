// addevens.cs - functions to sum the even entries in a array of int (with test)

using System;
using System.Linq;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class AddEvens {
    internal static int Way1(int[] seq)
    {
        var sum = 0;

        foreach (var k in seq)
            if (k % 2 == 0) sum += k;

        return sum;
    }

    internal static int Way2(int[] seq)
    {
        return seq.Where(k => k % 2 == 0).Sum();
    }
}

internal static class Program {
    private static int Main()
    {
        int[] seq = { 5, 2, 9, 0, -3, 8, 7, 1, -13, 6, -5, -10, 18, 4, 13, -1 };

        var sum = AddEvens.Way2(seq);
        bool ok = sum == AddEvens.Way1(seq);

        Console.WriteLine("Got {0}, which appears {1}",
                          sum, (ok ? "correct." : "WRONG!"));

        return ok ? 0 : 1;
    }
}
