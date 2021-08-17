using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal class Trie<T> : Dictionary<T, Trie<T>> { }

internal static class TrieEx {
    internal static Trie<T> Grow<T>(this Trie<T> self, T key)
    {
        Trie<T> child;

        if (!self.TryGetValue(key, out child)) {
            child = new Trie<T>();
            self.Add(key, child);
        }

        return child;
    }

    internal static Trie<T> Grow<T>(this Trie<T> self, IEnumerable<T> chain)
    {
        foreach (var key in chain) self = self.Grow(key);
        return self;
    }

    internal static Trie<T> Climb<T>(this Trie<T> self, IEnumerable<T> chain)
    {
        foreach (var key in chain)
            if (!self.TryGetValue(key, out self)) return null;

        return self;
    }

    internal static int CountLeaves<T>(this Trie<T> self) // 1, for a leaf
            => self.Count == 0 ? 1 : self.Values.Sum(CountLeaves);

    internal static int CountLeaves<T>(this Trie<T> self, IEnumerable<T> chain)
            => self.Climb(chain)?.CountLeaves() ?? 0;
}

internal static class Solution {
    private static void Main()
    {
        const string suf = "_";
        var trie = new Trie<char>();

        foreach (var n in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var a = Console.ReadLine().Split();

            switch (a[0]) {
            case "add":
                trie.Grow(Enumerable.Concat(a[1], suf));
                continue;

            case "find":
                Console.WriteLine(trie.CountLeaves(a[1]));
                continue;
            }
        }
    }
}
