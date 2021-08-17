using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

internal sealed class Problem {
    private int[] Coins;

    private Dictionary<Tuple<int, int>, long> Memo
            = new Dictionary<Tuple<int, int>, long>();

    public Problem(string line)
    {
        Coins = Array.ConvertAll(line.Split(), int.Parse);
    }

    private long Solve(int index, int subtotal)
    {
        if (subtotal == 0) return 1L;
        if (index == Coins.Length) return 0L;

        var key = Tuple.Create(index, subtotal);

        long count;
        if (Memo.TryGetValue(key, out count)) return count;

        var coin = Coins[index];
        var next_index = index + 1;

        count = 0L;
        for (var next_subtotal = subtotal; next_subtotal >= 0;
                                           next_subtotal -= coin)
            count += Solve(next_index, next_subtotal);

        Memo[key] = count;
        return count;
    }

    public long Solve(int total) => Solve(0, total);
}

internal static class Solution {
    private static void Main()
    {
        var total = Console.ReadLine().Split().Select(int.Parse).First();
        Console.WriteLine(new Problem(Console.ReadLine()).Solve(total));
    }
}
