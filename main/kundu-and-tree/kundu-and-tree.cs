using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

// Disjoint sets implemented via union by size with full path compression.
internal sealed class DisjointSets {
    internal DisjointSets(int vertexCount)
    {
        _elems = new int[vertexCount];
        for (var i = 0; i != vertexCount; ++i) _elems[i] = -1;
    }

    internal IEnumerable<int> GetComponentSizes()
        => _elems.Where(val => val < 0).Select(val => -val);

    internal void Union(int i, int j)
    {
        // find what sets i and j are, and stop if they are already the same
        i = Find(i);
        j = Find(j);
        if (i == j) return;

        // unite the sets by size (which is stored negated)
        if (_elems[i] < _elems[j])
            Join(i, j); // set i is bigger; have it absorb set j
        else
            Join(j, i); // set j is bigger (or same size); have it absorb set i

    }

    private int Find(int i)
    {
        // find the ancestor
        var j = i;
        while (_elems[j] >= 0) j = _elems[j];

        // compress the path
        while (i != j) {
            var parent = _elems[i];
            _elems[i] = j;
            i = parent;
        }

        return j;
    }

    private void Join(int parent, int child)
    {
        _elems[parent] += _elems[child];
        _elems[child] = parent;
    }

    private readonly int[] _elems;
}

internal static class Combinatorics {
    private const long Mod = 1000000007L;

    private static List<long> CountPairs(this IList<long> sizes)
    {
        var sum = sizes.Sum();
        return sizes.Select(size => size * (sum -= size)).ToList();
    }

    private static IEnumerable<long> CountTriplets(this List<long> sizes)
    {
        var pairCounts = sizes.CountPairs();
        var sum = pairCounts.Sum();

        return sizes.Zip(pairCounts,
                         (size, pairCount) => size * (sum -= pairCount) % Mod);
    }

    internal static long CountAllTriplets(this IEnumerable<int> sizes)
        => sizes.Select(Convert.ToInt64).ToList().CountTriplets().Sum() % Mod;
}

internal static class Solution {
    private static DisjointSets ReadSets(int vertexCount, int edgeCount)
    {
        var sets = new DisjointSets(vertexCount);

        while (edgeCount-- > 0) {
            var tokens = Console.ReadLine().Split();

            if (tokens[2] == "b")
                sets.Union(int.Parse(tokens[0]), int.Parse(tokens[1]));
        }

        return sets;
    }

    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());

        var sets = ReadSets(n + 1,  // not using vertex 0 so got n + 1 vertices
                            n - 1); // a tree has one fewer edge than vertex

        var sizes = sets.GetComponentSizes().Skip(1); // not using vertex 0
        Console.WriteLine(sizes.CountAllTriplets());
    }
}
