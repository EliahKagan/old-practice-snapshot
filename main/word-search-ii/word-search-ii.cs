internal class CharMap<T> { // maps from a lower-case English letter to a T
    public const string Alpha = "abcdefghijklmnopqrstuvwxyz";

    private const int AlphaLen = 'z' - 'a' + 1;

    static CharMap() {
        for (var i = 0; i != AlphaLen; ++i) {
            if (Alpha[i] - 'a' != i) {
                throw new NotSupportedException(
                        "English lower-case letters are noncontiguous");
            }
        }
    }

    public T this[char ch] {
        get => _elems[ch - 'a'];
        set => _elems[ch - 'a'] = value;
    }

    private T[] _elems = new T[AlphaLen];
}

internal sealed class Trie : CharMap<Trie> {
    public string Word { get; private set; }

    public Trie(params string[] words) {
        foreach (var word in words) {
            var cur = this;
            foreach (var ch in word) cur = cur[ch] ?? (cur[ch] = new Trie());
            cur.Word = word;
        }
    }

#if WITH_DUMP_LOGIC
    private object ToDump() {
        IDictionary<string, object> repr = new System.Dynamic.ExpandoObject();

        foreach (var ch in Alpha) {
            var child = this[ch];
            if (child != null) repr[ch.ToString()] = child;
        }

        if (Word != null) repr[nameof(Word)] = Word;

        return repr;
    }
#endif
}

public class Solution {
    public IList<string> FindWords(char[,] board, string[] words) {
        const char visited = '\0';
        var istop = board.GetLength(0);
        var jstop = board.GetLength(1);
        var matches = new List<string>();

        void Dfs(Trie trie, int i, int j) {
            if (i == -1 || i == istop || j == -1 || j == jstop) return;

            var ch = board[i, j];
            if (ch == visited) return;

            trie = trie[ch];
            if (trie == null) return;

            if (trie.Word != null) matches.Add(trie.Word);

            board[i, j] = visited;
            Dfs(trie, i, j - 1);
            Dfs(trie, i, j + 1);
            Dfs(trie, i - 1, j);
            Dfs(trie, i + 1, j);
            board[i, j] = ch;
        }

        var root = new Trie(words);
        for (var i = 0; i != istop; ++i)
            for (var j = 0; j != jstop; ++j) Dfs(root, i, j);

        return matches.Distinct().ToList();
    }
}
