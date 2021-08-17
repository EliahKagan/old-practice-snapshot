<Query Kind="Program" />

public class WordFilter {
    public WordFilter(string[] words) {
        for (var i = 0; i != words.Length; ++i) _trie.AddWord(words[i], i);
    }
    
    public int F(string prefix, string suffix)
        => _trie.FindWeight(prefix, suffix);
    
    private readonly Trie _trie = new Trie();
    
    private sealed class Trie : Dictionary<ValueTuple<char, char>, Trie> {
        internal Trie() : this(0) { }
    
        internal void AddWord(string word, int weight) {
            var cur = this;
            cur._weight = weight;
            
            var n = word.Length;
            for (var i = 0; i != n; ++i) {
                var key = (word[i], word[n - 1 - i]);
                
                if (cur.TryGetValue(key, out var next)) {
                    next._weight = weight;
                } else {
                    next = new Trie(weight);
                    cur.Add(key, next);
                }
                
                cur = next;
            }
        }
        
        internal int FindWeight(string prefix, string suffix) {        
            var n = Math.Max(prefix.Length, suffix.Length);
            
            if (prefix.Length != n) prefix = prefix.PadRight(n, '\0');
            else if (suffix.Length != n) suffix = suffix.PadLeft(n, '\0');
            
            
        }
        
        private Trie(int weight) => _weight = weight;
    
        private int _weight;
    }
}
