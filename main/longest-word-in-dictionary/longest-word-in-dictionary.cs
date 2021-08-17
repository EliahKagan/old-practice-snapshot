internal sealed class Trie {
    internal void Add(string word) {
        var cur = this;

        foreach (var ch in word) {
            if (cur._children == null) cur._children = new Trie['z' - 'a' + 1];
            var k = ch - 'a';
            cur = cur._children[k] ?? (cur._children[k] = new Trie());
        }

        cur._word = word;
    }

    internal string FindBest() {
        var best = _word;
        if (best == null) throw new InvalidOperationException();

        void Dfs(Trie node) {
            var leaf = true;

            if (node._children != null) {
                foreach (var child in node._children) {
                    if (child != null && child._word != null) {
                        leaf = false;
                        Dfs(child);
                    }
                }
            }

            if (leaf && best.Length < node._word.Length) best = node._word;
        }

        Dfs(this);
        return best;
    }

    private Trie[] _children = null;

    private string _word = null;
}

public class Solution {
    public string LongestWord(params string[] words) {
        var trie = new Trie();
        trie.Add("");
        foreach (var word in words) trie.Add(word);
        return trie.FindBest();
    }
}
