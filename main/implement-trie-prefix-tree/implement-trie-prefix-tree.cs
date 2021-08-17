public class Trie {
    /** Inserts a word into the trie. */
    public void Insert(string word) {
        var node = this;

        foreach (var k in word.Select(ch => ch - 'a')) {
            if (node._children == null) node._children = new Trie[AlphaLen];
            if (node._children[k] == null) node._children[k] = new Trie();
            node = node._children[k];
        }

        node._endsWord = true;
    }

    /** Returns if the word is in the trie. */
    public bool Search(string word) {
        var node = FindNode(word);
        return node != null && node._endsWord;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    public bool StartsWith(string prefix) {
        // In case prefix is empty, also ensure the trie is nonempty.
        return FindNode(prefix) != null && _children != null;
    }

    private Trie FindNode(string text) {
        var node = this;

        foreach (var k in text.Select(ch => ch - 'a')) {
            if (node._children == null) return null;
            node = node._children[k];
            if (node == null) return null;
        }

        return node;
    }

    private const int AlphaLen = 'z' - 'a' + 1;

    private Trie[] _children = null;

    private bool _endsWord = false;
}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.Insert(word);
 * bool param_2 = obj.Search(word);
 * bool param_3 = obj.StartsWith(prefix);
 */
