using System;
using System.Collections.Generic;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal sealed class Trie<T> : Dictionary<T, Trie<T>> { }

internal static class TrieEx {
    /// <summary>
    /// Adds a chain to a trie. Assumes none of its links are already present.
    /// </summary>
    /// <typeparam name="T">The type of keys in the chain.</typeparam>
    /// <param name="self">The trie that is to be grown.</param>
    /// <param name="en">An enumerator to the beginning of the chain that is to
    /// be added. MoveNext() will _not_ be called on it before it is used
    /// the first time.</param>
    private static void Attach<T>(this Trie<T> self, IEnumerator<T> en)
    {
        do {
            var child = new Trie<T>();
            self.Add(en.Current, child);
            self = child;
        }
        while (en.MoveNext());
    }

    /// <summary>
    /// Adds a chain to a trie if none of its links are already present.
    /// </summary>
    /// <typeparam name="T">The type of keys in the chain.</typeparam>
    /// <param name="self">The trie that is to be grown.</param>
    /// <param name="en">An enumerator to the beginning of the chain that is to
    /// be added. MoveNext() will be called on it before it is used.</param>
    /// <returns>True if the chain was added (including if the chain was
    /// empty, thus vacuously added). False if it couldn't be added.</returns>
    private static bool Sprout<T>(this Trie<T> self, IEnumerator<T> en)
    {
        if (en.MoveNext()) {
            Trie<T> child;
            if (self.TryGetValue(en.Current, out child)) return false;
            Attach(self, en);
        }

        return true;
    }

    /// <summary>
    /// Detects if a chain is a nonempty sub- or superchain of any chain already
    /// added. If not, adds it. If so, returns true and may (partially) add it.
    /// </summary>
    /// <typeparam name="T">The type of keys in the chain.</typeparam>
    /// <param name="self">The trie that is to be grown.</param>
    /// <param name="chain">The chain that is to be added to the trie.</param>
    /// <returns>True if chain is a nonempty sub- or superchain of any chain
    /// already added, and false otherwise.</returns>
    internal static bool Grow<T>(this Trie<T> self, IEnumerable<T> chain)
    {
        using (var en = chain.GetEnumerator()) {
            if (self.Sprout(en)) return false;
            for (self = self[en.Current]; en.MoveNext(); ) {
                Trie<T> child;
                if (self.TryGetValue(en.Current, out child)) self = child;
                else if (self.Count == 0) return true;
                else {
                    self.Attach(en);
                    return false;
                }
            }
        }

        return true;
    }
}

internal static class Solution {
    private static void Main()
    {
        var trie = new Trie<char>();

        for (var n = int.Parse(Console.ReadLine()); n > 0; --n) {
            var s = Console.ReadLine().Trim();
            if (trie.Grow(s)) {
                Console.WriteLine("BAD SET");
                Console.WriteLine(s);
                return;
            }
        }

        Console.WriteLine("GOOD SET");
    }
}
