class Trie {
    /** Inserts a word into the trie. */
    public void insert(final String word) {
        Trie node = this;

        for (int i = 0; i != word.length(); ++i) {
            if (node._children == null) node._children = new Trie[ALPHA_LEN];
            final int k = word.charAt(i) - 'a';
            if (node._children[k] == null) node._children[k] = new Trie();
            node = node._children[k];
        }

        node._endsWord = true;
    }

    /** Returns if the word is in the trie. */
    public boolean search(final String word) {
        final Trie node = findNode(word);
        return node != null && node._endsWord;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    public boolean startsWith(final String prefix) {
        // In case prefix is empty, also ensure the trie is nonempty.
        return findNode(prefix) != null && _children != null;
    }

    private Trie findNode(final String word) {
        Trie node = this;

        for (int i = 0; i != word.length(); ++i) {
            if (node._children == null) return null;
            node = node._children[word.charAt(i) - 'a'];
            if (node == null) return null;
        }

        return node;
    }

    private Trie[] _children = null;

    private boolean _endsWord = false;

    private static final int ALPHA_LEN = 'z' - 'a' + 1;
}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * boolean param_2 = obj.search(word);
 * boolean param_3 = obj.startsWith(prefix);
 */
