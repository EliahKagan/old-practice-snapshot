using System;
using System.Collections.Generic;

[assembly: System.Reflection.AssemblyVersion("1.1.0.0")]

internal sealed class Trie<T> : Dictionary<T, Trie<T>> {
    private int traversals = 1;

    internal void Grow(IEnumerable<T> chain)
    {
        var parent = this;

        foreach (var key in chain) {
            Trie<T> child;

            if (parent.TryGetValue(key, out child)) ++child.traversals;
            else parent.Add(key, child = new Trie<T>());

            parent = child;
        }
    }

    internal int PrefixCount(IEnumerable<T> chain)
    {
        var node = this;

        foreach (var key in chain)
            if (!node.TryGetValue(key, out node)) return 0;

        return node.traversals;
    }
}

internal static class Solution {
    private static void Main()
    {
        var trie = new Trie<char>();

        for (var n = int.Parse(Console.ReadLine()); n > 0; --n) {
            var a = Console.ReadLine().Split();

            switch (a[0]) {
            case "add":
                trie.Grow(a[1]);
                continue;

            case "find":
                Console.WriteLine(trie.PrefixCount(a[1]));
                continue;
            }
        }
    }
}
