// sorting2.cs - recursive LINQ-based non-in-place quicksort-like sort
//     slightly less inelegant version using LINQ GroupBy operator to partition

#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Numerics;

[assembly: System.Reflection.AssemblyVersion("0.2.0.0")]

internal static class Program {
    private static IEnumerable<T> Sort<T>(this IEnumerable<T> v)
        where T : IComparable<T>
    {
        Contract.Assert(v != null);

        if (!v.Any()) return Enumerable.Empty<T>();

        var e = v.First();
        var p = v.GroupBy(x => x.CompareTo(e));
        return p.Where(g => g.Key < 0).SelectMany(g => g).Sort()
                .Concat(p.Where(g => g.Key == 0).SelectMany(g => g))
                .Concat(p.Where(g => g.Key > 0).SelectMany(g => g).Sort());
    }

    private static void SortOut<T>(this IEnumerable<T> v)
        where T : IComparable<T>
    {
        Contract.Assert(v != null);
        Console.WriteLine(string.Join(", ", v.Sort()));
    }

    private static void Main()
    {
        new[] { 1, 5, 23, 18, 9, 1, 3 }.SortOut();
        new[] { 2.3, 8.5, 1.6, 4.4, 6.8, 0.9 }.SortOut();
        new[] { "foo", "bar", "baz", "foobar", "quux" }.SortOut();
        Enumerable.Range(10, 11).Select(i => -(BigInteger)i).SortOut();
        new bool[] { }.SortOut();
    }
}
