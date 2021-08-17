<Query Kind="Program" />

internal static class Combinatorics {
    internal static bool Advance(int len, int[] cycles, int[] orders)
    {
        var i = 0;
        while (i != len && cycles[i] == orders[i]) ++i;
        if (i == len) return false;

        for (var j = 0; j != i; ++j) cycles[j] = 0;
        ++cycles[i];
        return true;
    }
}

private static class UnitTest {
    private static void Main()
    {
        int[] orders = { 2, 1, 3, 1 }, cycles = { 0, 0, 0, 0 };
        var len = orders.Length;
        
        do Console.WriteLine(string.Join(" ", cycles));
        while (Combinatorics.Advance(len, cycles, orders));
        
        Console.WriteLine();
        
        var b = Enumerable.Repeat(9, 2).ToArray();
        var d = Enumerable.Repeat(0, 2).ToArray();
        
        do Console.WriteLine(string.Concat(d.Reverse()));
        while (Combinatorics.Advance(2, d, b));
    }
}