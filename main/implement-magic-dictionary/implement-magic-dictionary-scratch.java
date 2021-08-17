class MagicDictionary {
    /** Build a dictionary through a list of words */
    public void buildDict(final String[] dict) {
        _children = null;
        _endsWord = false;

        for (final String word : dict) {
            MagicDictionary cur = this;

            for (int i = 0; i != word.length(); ++i) {
                if (cur._children == null)
                    cur._children = new MagicDictionary['z' - 'a' + 1];

                final int k = key(word, i);
                MagicDictionary next = cur._children[k];
                if (next == null)
                    next = cur._children[k] = new MagicDictionary();

                cur = next;
            }

            cur._endsWord = true;
        }
    }

    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    public boolean search(final String word) {
        return searchModify(word, 0);
    }

    private static int key(final String word, final int i) {
        return word.charAt(i) - 'a';
    }

    private boolean searchModify(final String word, final int i) {
        if (i == word.length() || _children == null) return false;

        final int kk = key(word, i);
        if (_children[kk] != null && _children[kk].searchModify(word, i + 1))
            return true;

        for (int k = 0; k != _children.length; ++k) {
            if (_children[k] != null && k != kk
                    && _children[k].searchLiteral(word, i + 1))
                return true;
        }

        return false;
    }

    private boolean searchLiteral(final String word, int i) {
        MagicDictionary cur = this;

        for (; i != word.length(); ++i) {
            if (cur._children == null) return false;
            cur = cur._children[key(word, i)];
            if (cur == null) return false;
        }

        return cur._endsWord;
    }

    private MagicDictionary[] _children = null;

    private boolean _endsWord = false;
}

final class UnitTest {
    public static void main(final String[] args) {
        final MagicDictionary dict = new MagicDictionary();
        dict.buildDict(new String[] { "hello", "leetcode" });
        p(dict.search("hello"));
        p(dict.search("hhllo"));
        p(dict.search("hell"));
        p(dict.search("leetcoded"));
        p(dict.search("lzetcode"));
        p(dict.search("lzetcodq"));
        p(dict.search("leetcode"));
    }

    private static void p(final Object obj) {
        System.out.println(obj);
    }

    private UnitTest() { throw new AssertionError(); }
}
