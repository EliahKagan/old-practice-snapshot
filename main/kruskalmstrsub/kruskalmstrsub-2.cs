using System;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.1.0.0")]

internal sealed class DisjointSets {
    /// <summary>Creates the specified number of disjoint singletons.</summary>
    /// <param name="count">The number of singleton sets to make.</param>
    public DisjointSets(int count)
    {
        _elems = new int[count];
        for (var i = 0; i != count; ++i) _elems[i] = -1;
    }

    /// <summary>Joins the set that has i with the set that has j.</summary>
    /// <param name="i">An element of the first set to be joined.</param>
    /// <param name="j">An element of the second set to be joined.</param>
    /// <returns>True if i and j were not already in the same set.</returns>
    public bool Union(int i, int j)
    {
        i = FindSet(i);
        j = FindSet(j);
        if (i == j) return false;

        // Unite the sets by rank.
        if (_elems[i] > _elems[j]) {
            _elems[i] = j; // j has superior (more negative) rank
        } else {
            // if i and j have equal rank, then promote i
            if (_elems[i] == _elems[j]) --_elems[i];

            _elems[j] = i; // i has superior (more negative) rank
        }

        return true;
    }

    /// <summary>Finds the representative element of the set with i.</summary>
    /// <param name="i">The member whose set representative is sought.</param>
    /// <returns>The representative (ancestor) element.</returns>
    private int FindSet(int i)
    {
        // Find the ancestor.
        var j = i;
        while (_elems[j] >= 0) j = _elems[j];

        // Compress the path.
        while (i != j) {
            var p = _elems[i];
            _elems[i] = j;
            i = p;
        }

        return j;
    }

    private readonly int[] _elems;
}

internal struct Edge {
    public Edge(int x, int y, int r)
    {
        X = x;
        Y = y;
        R = r;
    }

    public Edge(int[] a) : this(a[0], a[1], a[2]) { }

    public readonly int X, Y, R;
}

internal static class Solution {
    private static void Main()
    {
        var ve = ReadRecord();
        var v = ve[0];
        var e = ve[1];

        var sets = new DisjointSets(v + 1); // because we're not using 0

        // Each MST has the same weight sum so we don't need the "special" one.
        Console.WriteLine(Enumerable.Range(0, e)
                            .Select(_ => new Edge(ReadRecord()))
                            .OrderBy(edge => edge.R)
                            .Where(edge => sets.Union(edge.X, edge.Y))
                            .Sum(edge => edge.R));
    }

    private static int[] ReadRecord()
        => Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
}
