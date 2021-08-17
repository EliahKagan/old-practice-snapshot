using System;

[assembly:System.Reflection.AssemblyVersion("1.0.0.0")]

internal sealed class DisjointSets {
    internal DisjointSets(int n)
    {
        _elems = new Element[n + 1];

        for (var i = 0; i != _elems.Length; ++i) {
            _elems[i].Parent = i;
            _elems[i].Size = 1;
        }
    }

    internal void Union(int i, int j) // union by size
    {
        i = FindSet(i);
        j = FindSet(j);
        if (i == j) return;

        if (_elems[i].Size < _elems[j].Size) {
            _elems[j].Size += _elems[i].Size;
            _elems[i].Parent = j;
        } else {
            _elems[i].Size += _elems[j].Size;
            _elems[j].Parent = i;
        }
    }

    internal int GetSize(int i) => _elems[FindSet(i)].Size;

    private int FindSet(int i)
    {
        var j = i;
        while (j != _elems[j].Parent) j = _elems[j].Parent;

        while (i != j) { // path compression
            var p = _elems[i].Parent;
            _elems[i].Parent = j;
            i = p;
        }

        return j;
    }

    private readonly Element[] _elems;

    private struct Element {
        internal int Parent;
        internal int Size;
    }
}

internal static class Solution {
    private static void Main()
    {
        var nq = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        var n = nq[0];
        var q = nq[1];

        for (var sets = new DisjointSets(n); q > 0; --q) {
            var tok = Console.ReadLine().Split();

            if (tok[0] == "M") sets.Union(int.Parse(tok[1]), int.Parse(tok[2]));
            else Console.WriteLine(sets.GetSize(int.Parse(tok[1])));
        }
    }
}
