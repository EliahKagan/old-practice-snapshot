import java.util.HashMap;
import java.util.Map;

final class Trie {
    void add(final String chain, final int weight) {
        Trie cur = this;
        cur._weight += weight;

        for (int i = 0; i != chain.length(); ++i) {
            final int k = chain.charAt(i) - 'a';
            Trie next = cur._children[k];
            if (next == null) next = cur._children[k] = new Trie();

            cur = next;
            cur._weight += weight;
        }
    }

    int weight(final String prefix) {
        Trie cur = this;

        for (int i = 0; i != prefix.length(); ++i) {
            cur = cur._children[prefix.charAt(i) - 'a'];
            if (cur == null) return 0;
        }

        return cur._weight;
    }

    private final Trie[] _children = new Trie['z' - 'a' + 1];

    private int _weight = 0;
}

class MapSum {
    public void insert(final String key, final int val) {
        final int delta = val - _weights.getOrDefault(key, 0);
        _weights.put(key, val);
        _trie.add(key, delta);
    }

    public int sum(String prefix) {
        return _trie.weight(prefix);
    }

    private final Trie _trie = new Trie();

    private final Map<String, Integer> _weights = new HashMap<>();
}

final class UnitTest {
    public static void main(final String[] args) {
        final MapSum ms = new MapSum();
        ms.insert("apple", 3);
        p(ms.sum("ap"));
        ms.insert("app", 2);
        p(ms.sum("ap"));
        ms.insert("apple", 7);
        p(ms.sum("ap"));
        p(ms.sum("quux"));
        ms.insert("apple", 2);
        p(ms.sum("app"));
        p(ms.sum("appl"));
    }

    private static void p(final Object obj) {
        System.out.println(obj);
    }

    private UnitTest() { throw new AssertionError(); }
}
