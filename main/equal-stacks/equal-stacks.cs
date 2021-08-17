using System.Collections.Generic;
using System.Linq;
using static System.Array;
using static System.Console;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class EnumerableEx {
    internal static IEnumerable<int> RunningSum(this IEnumerable<int> self)
    {
        var acc = 0;
        yield return acc;
        foreach (var elem in self) yield return acc += elem;
    }
}

internal static class Solution {
    private static string[] ReadWords() => ReadLine().Split(' ');

    private static int[] GetRecord() => ConvertAll(ReadWords(), int.Parse);

    private static Stack<int> GetStack() => // gets a stack of absolute heights
        new Stack<int>(ReadWords().Select(int.Parse).Reverse().RunningSum());

    private static Stack<int>[] GetAllStacks(this int[] ns) =>
        ConvertAll(ns, n => GetStack()); // currently, we don't check n-values

    // Finds max element present in all "height" stacks in nonempty hs. Each
    // stack in hs must be sorted decreasingly (top element always greatest).
    private static int MaxLevelHeight(this IEnumerable<Stack<int>> hs)
    {
        for (; ; ) {
            var min = hs.Min(h => h.Peek());
            var to_trim = hs.Where(h => h.Peek() > min);
            if (!to_trim.Any()) return hs.First().Peek();
            foreach (var h in to_trim) h.Pop();
        }
    }

    private static void Main() =>
        WriteLine(GetRecord().GetAllStacks().MaxLevelHeight());
}
