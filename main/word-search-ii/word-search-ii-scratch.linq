<Query Kind="Program" />

internal struct CharMap<T> { // maps from a lower-case English letter to a T
    private const int AlphaLen = 'z' - 'a' + 1;
    
    static CharMap() {
        // Trace.Assert, Debug.Assert and Contract.Assert don't work on
        // leetcode.com, so I must throw an exception instead.
        var alpha = "abcdefghijklmnopqrstuvwxyz";
        for (var i = 0; i != AlphaLen; ++i) {
            if (alpha[i] - 'a' != i) {
                throw new NotSupportedException(
                        "English lower-case letters are noncontiguous");
            }
        }
    }
    
    public T this[char ch] {
        get {
            Init();
            return _elems[ch - 'a'];
        }
        
        set {
            Init();
            _elems[ch - 'a'] = value;
        }
    }
    
    private void Init() {
        if (_elems == null) _elems = new T[AlphaLen];
    }
    
    private T[] _elems;
}

internal struct Trie {
    public CharMap<Trie> Children { get; private set; }
    
    public string Word { get; private set; }
    
    public void Add(string word) {
        var cur = this;
        foreach (var ch in word) cur = cur.Children[ch];
        cur.Word = word;
    }
}

private static void Main() {
    var trie = new Trie();
    trie.Add("road");
    trie.Add("ropes");
    //trie.Dump();
}