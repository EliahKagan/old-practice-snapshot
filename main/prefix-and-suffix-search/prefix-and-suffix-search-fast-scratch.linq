<Query Kind="Program" />

internal static class Extensions {
    internal static IEnumerable<T> Row<T>(this Queue<T> self)
        => Enumerable.Range(0, self.Count).Select(_ => self.Dequeue());
}

internal sealed class Trie {
    // Adds a chain with the specified weight. This overwrites existing
    // weight information for its links, so chains should be added in order
    // of increasing weight, for FindMaxWeight() to be reliable.
    internal void Add(IEnumerable<char> chain, int weight) {
        var cur = this;
        cur._weight = weight;
        
        foreach (var ch in chain) {
            if (cur._children == null) cur._children = new Trie['z' - 'a' + 1];
            var next = cur._children[ch - 'a'];
            if (next == null) next = cur._children[ch - 'a'] = new Trie();
            next._weight = weight;
            cur = next;
        }
    }
    
    // Finds the maximum weight of any chain matched by the chain argument,
    // where '\0' in the chain argument matches any character and every other
    // character in it is treated literally.
    internal int FindMaxWeight(IEnumerable<char> chain) {
        var q = new Queue<Trie>();
        q.Enqueue(this);
        
        foreach (var ch in chain) {
            if (ch == '\0') {
                foreach (var cur in q.Row()) {
                    // Enqueue all the next level's nodes, as '\0' means "any."
                    if (cur._children != null) {
                        foreach (var next in cur._children)
                            if (next != null) q.Enqueue(next);
                    }
                }
            } else {
                foreach (var cur in q.Row()) {
                    // Enqueue just nodes that match the current character.
                    var next = cur._children?[ch - 'a'];
                    if (next != null) q.Enqueue(next);
                }
            }
            
            if (q.Count == 0) return NoWeight;
        }
        
        return q.Max(node => node._weight);
    }
    
    private const int NoWeight = -1;

    private Trie[] _children = null;
    
    private int _weight = NoWeight;
}

public class WordFilter {
    public WordFilter(string[] words) {
        for (var i = 0; i != words.Length; ++i)
            _trie.Add(InterleavePrefixSuffix(words[i]), i);
    }
    
    public int F(string prefix, string suffix)
        => _trie.FindMaxWeight(InterleavePrefixSuffix(prefix, suffix));
    
    private static IEnumerable<char> InterleavePrefixSuffix(string word) {
        var n = word.Length;
        
        for (var i = 0; i != n; ++i) {
            yield return word[i];
            yield return word[n - 1 - i];
        }
    }
    
    private static IEnumerable<char> InterleavePrefixSuffix(string prefix,
                                                            string suffix) {
        var n = Math.Max(prefix.Length, suffix.Length);
        if (prefix.Length != n) prefix = prefix.PadRight(n, '\0');
        else if (suffix.Length != n) suffix = suffix.PadLeft(n, '\0');
        
        for (var i = 0; i != n; ++i) {
            yield return prefix[i];
            yield return suffix[n - 1 - i];
        }
    }
    
    private Trie _trie = new Trie();
}

private static void Main() {
    var filter = new WordFilter(new[] { "ae", "bratwurst", "apple", "argyle",
        "foobarbazquux", "aaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" });
    filter.F("a", "e").Dump();
    filter.F("b", "").Dump();
    filter.F("aaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa").Dump();
    filter.F("aaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa").Dump();
}
