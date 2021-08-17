using System.Collections.Generic;
using System.Linq;
using static System.Console;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class ListEx {
    private static int FindMaxLessOrEqual(this List<long> seq, long key,
                                          int from, int to)
    {
        if (to < from) return to;

        var i = from + (to - from) / 2;

        if (key < seq[i]) return FindMaxLessOrEqual(seq, key, from, i - 1);
        if (key > seq[i]) return FindMaxLessOrEqual(seq, key, i + 1, to);
        return i;
    }

    // Returns the index of the last element of a not greater than n.
    // Assumes a is strictly increasing and contains such an element.
    internal static int FindMaxLessOrEqual(this List<long> seq, long key)
            => FindMaxLessOrEqual(seq, key, 0, seq.Count - 1);
}

internal static class Arith {
    internal static List<long> RunningSum(List<long> seq)
    {
        var sums = new List<long>(seq.Count);

        var acc = 0L;
        foreach (var elem in seq) sums.Add(acc += elem);

        return sums;
    }

    internal static List<long> EvenFibonacci(long max)
    {
        for (var seq = new List<long> { 0L, 2L }; ; ) {
            var elem = seq[seq.Count - 2] + seq[seq.Count - 1] * 4;

            if (elem >= max) {
                if (elem == max) seq.Add(elem);
                return seq;
            }

            seq.Add(elem);
        }
    }
}

internal static class Solution {
    private static List<long> ReadUpperBounds()
    {
        var t = int.Parse(ReadLine());
        var a = new List<long>(t);
        while (t-- > 0) a.Add(long.Parse(ReadLine()));
        return a;
    }

    private static void Main()
    {
        var bounds = ReadUpperBounds();
        var seq = Arith.EvenFibonacci(bounds.Max());
        var sums = Arith.RunningSum(seq);

        foreach (var n in bounds) WriteLine(sums[seq.FindMaxLessOrEqual(n)]);
    }
}
