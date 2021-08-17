using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    const long A = 'A' - 1L;

    private static int ReadValue() => int.Parse(Console.ReadLine());

    private static string ReadWord() => Console.ReadLine().Trim();

    private static string[] ReadNames()
            => Enumerable.Range(0, ReadValue())
                         .Select(i => ReadWord())
                         .OrderBy(word => word)
                         .ToArray();

    private static IEnumerable<long> RawScores(this IEnumerable<string> names)
            => from word in names select word.Sum(letter => letter - A);

    private static long[] Scores(this string[] names)
            => Enumerable.Range(1, names.Length)
                         .Zip(names.RawScores(), (i, n) => i * n)
                         .ToArray();

    private static void Main()
    {
        var names = ReadNames();
        var scores = names.Scores();

        foreach (var q in Enumerable.Range(0, ReadValue())) {
            var i = Array.BinarySearch(names, ReadWord());
            Console.WriteLine(i < 0 ? 0L : scores[i]);
        }
    }
}
