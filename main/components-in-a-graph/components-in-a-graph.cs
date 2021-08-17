using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal struct MinMax {
    internal MinMax(int min, int max)
    {
        Min = min;
        Max = max;
    }

    internal int Min { get; }

    internal int Max { get; }

    public override string ToString() => $"{Min} {Max}";
}

internal static class EnumerableInt32Extensions {
    internal static MinMax MinMax(this IEnumerable<int> self)
        => self.Aggregate(
                seed: new MinMax(min: int.MaxValue, max: int.MinValue),
                func: (acc, item) => new MinMax(min: Math.Min(acc.Min, item),
                                                max: Math.Max(acc.Max, item)));
}

internal sealed class DisjointSets {
    internal DisjointSets(int count)
    {
        _elems = new int[count];

        // Each element starts in a singleton set (cardinality 1).
        foreach (var i in Enumerable.Range(0, count)) _elems[i] = -1;
    }

    internal void Union(int i, int j)
    {
        // Find the ancestors and stop if they are already the same.
        i = FindSet(i);
        j = FindSet(j);
        if (i == j) return;

        // Unite by size. Sizes are stored as strictly negative values.
        if (_elems[i] > _elems[j]) {
            // The i-set is SMALLER than the j-set. Make j the parent.
            Join(parent: j, child: i);
        } else {
            // The i-set is at least as big as the j-set. Make i the parent.
            Join(parent: i, child: j);
        }
    }

    internal IEnumerable<int> ComponentSizes()
        => from e in _elems
           where e < 0
           select -e;

    private int FindSet(int i)
    {
        // Catches possible errors in client code.
        RangeCheck(nameof(i), i);

        // Find the ancestor.
        var j = i;
        while (_elems[j] >= 0) j = _elems[j];

        // Compress the path.
        while (i != j) {
            var parent = _elems[i];
            _elems[i] = j;
            i = parent;
        }

        return j;
    }

    private void Join(int parent, int child)
    {
        // Catches possible bugs. Might be better as assertions.
        RangeCheck(nameof(parent), parent);
        RangeCheck(nameof(child), child);

        _elems[parent] += _elems[child];
        _elems[child] = parent;
    }

    private void RangeCheck(string name, int i)
    {
        if (i < 0 || i >= _elems.Length)
            throw new ArgumentOutOfRangeException(paramName: name);
    }

    private readonly int[] _elems;
}

internal static class Solution {
    private static MinMax
    MinMaxNontrivialComponentSizes(this DisjointSets self)
        => self.ComponentSizes().Where(count => count > 1).MinMax();

    private static int[] ReadRecord()
    {
        var tokens = Console.ReadLine()
                            .Split((char[])null,
                                   StringSplitOptions.RemoveEmptyEntries);

        return Array.ConvertAll(tokens, int.Parse);
    }

    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var sets = new DisjointSets(n * 2 + 1);

        foreach (var t in Enumerable.Range(0, n)) {
            var record = ReadRecord();
            sets.Union(record[0], record[1]);
        }

        Console.WriteLine(sets.MinMaxNontrivialComponentSizes());
    }
}
