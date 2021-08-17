<Query Kind="Program" />

internal static class Extensions {
    internal static int FirstOr(this IEnumerable<int> self, int defaultValue)
        => self.DefaultIfEmpty(defaultValue).First();

    // Returns the first value at which two sequences intersect, if it exists.
    internal static int? DescendingIntersection(this IEnumerable<int> self,
                                                IEnumerable<int> other) {
        using (var a = self.GetEnumerator())
        using (var b = other.GetEnumerator()) {
            if (!(a.MoveNext() && b.MoveNext())) return null;
            
            for (; ; ) {
                if (a.Current > b.Current) { // too big at a
                    if (!a.MoveNext()) return null;
                }
                else if (a.Current != b.Current) { // too big at b
                    if (!b.MoveNext()) return null;
                }
                else return a.Current;
            }
        }
    }
}

internal class Trie {
    protected void AddChain(IEnumerable<char> chain, short weight) {
        // As a space optimization, I avoid populating weights at the root,
        // since they will always be the complete list of weights. However,
        // this does make the GetWeights() abstraction leakier: the caller
        // must take responsibility for treating empty prefixes and suffixes
        // specially.
        var cur = this;
        foreach (var ch in chain) {
            cur = cur[ch];
            cur._weights.Add(weight);
        }
    }
    
    protected IEnumerable<int> GetSubchainWeights(IEnumerable<char> subchain) {
        var cur = this;
        foreach (var ch in subchain) {
            // _children or _children[ch - 'a'] may be null, and this[ch] should
            // not be used here, because that creates missing branches.
            cur = cur._children?[ch - 'a'];
            if (cur == null) return NoWeights;
        }
        
        if (cur == this) { // see the comment in AddChain() above
            throw new ArgumentException(
                    "the empty subchain's weights are not stored",
                    nameof(subchain));
        }
        
        return cur._weights.Select(Convert.ToInt32);
    }
    
    protected Trie() { }
    
    // This is really a helper function for AddChain(). It creates missing
    // nodes automatically, like operator[] on a std::map in C++.
    private Trie this[char ch] {
        get {
            if (_children == null) _children = new Trie[AlphaLen];
            var i = ch - 'a';
            return _children[i] ?? (_children[i] = new Trie());
        }
    }
    
    private const int AlphaLen = 'z' - 'a' + 1;
    
    private static int[] NoWeights = new int[0]; // for GetSubchanWeights()

    private readonly List<short> _weights = new List<short>();
    
    private Trie[] _children;
}

internal sealed class PrefixTrie : Trie {
    internal void AddAllPrefixes(string word, int weight)
        => AddChain(word, (short)weight);
    
    internal IEnumerable<int> GetPrefixWeights(string prefix)
        => GetSubchainWeights(prefix);
}

internal sealed class SuffixTrie : Trie {
    internal void AddAllSuffixes(string word, int weight)
        => AddChain(word.Reverse(), (short)weight);
    
    internal IEnumerable<int> GetSuffixWeights(string suffix)
        => GetSubchainWeights(suffix.Reverse());
}

public class WordFilter {
    public WordFilter(string[] words) {
        _maxWeight = words.Length - 1;
    
        for (var weight = _maxWeight; weight != -1; --weight) {
            _prefixes.AddAllPrefixes(words[weight], weight);
            _suffixes.AddAllSuffixes(words[weight], weight);
        }
    }
    
    public int F(string prefix, string suffix) {
        if (prefix.Length == 0) {
            // _maxWeight is -1 when there were no words, so this works.
            if (suffix.Length == 0) return _maxWeight;
            return _suffixes.GetSuffixWeights(suffix).FirstOr(FallbackWeight);
        }
        
        if (suffix.Length == 0)
            return _prefixes.GetPrefixWeights(prefix).FirstOr(FallbackWeight);
        
        return _prefixes.GetPrefixWeights(prefix)
                .DescendingIntersection(_suffixes.GetSuffixWeights(suffix))
                ?? FallbackWeight;
    }
    
    private const int FallbackWeight = -1;
    
    private readonly int _maxWeight;
    private readonly PrefixTrie _prefixes = new PrefixTrie();
    private readonly SuffixTrie _suffixes = new SuffixTrie();
}

private static void Main() {
    var filter = new WordFilter(new[] { "ae", "bratwurst", "apple", "argyle",
        "foobarbazquux", "aaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" });
    filter.F("a", "e").Dump();
    filter.F("b", "").Dump();
    filter.F("aaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa").Dump();
    filter.F("aaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa").Dump();
}
