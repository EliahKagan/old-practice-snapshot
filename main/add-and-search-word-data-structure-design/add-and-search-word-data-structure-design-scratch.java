import java.util.ArrayDeque;
import java.util.HashMap;
import java.util.Map;
import java.util.Queue;
import java.util.function.Consumer;

class WordDictionary {
    /** Adds a word into the data structure. */
    public void addWord(final String word) {
        WordDictionary cur = this;

        for (int i = 0; i != word.length(); ++i) {
            cur = cur._children.computeIfAbsent(word.charAt(i),
                    key -> new WordDictionary());
        }

        cur._terminal = true;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    public boolean search(final String word) {
        final Queue<WordDictionary> q = new ArrayDeque<>();
        q.add(this);

        for (int i = 0; i != word.length(); ++i) {
            final char ch = word.charAt(i);

            if (ch == '.') {
                for (int width = q.size(); width != 0; --width) {
                    // . means any char, so enqueue all the next level's nodes
                    q.addAll(q.remove()._children.values());
                }
            } else {
                for (int width = q.size(); width != 0; --width) {
                    // enqueue only the nodes that match ch literally, if any
                    final WordDictionary child = q.remove()._children.get(ch);
                    if (child != null) q.add(child);
                }
            }

            if (q.isEmpty()) return false; // a simple optimization
        }

        return q.stream().anyMatch(node -> node._terminal);
    }

    private final Map<Character, WordDictionary> _children = new HashMap<>();

    private boolean _terminal = false;
}

final class UnitTest {
    public static void main(final String[] args) {
        final WordDictionary trie = new WordDictionary();

        final Consumer<String> test = word -> System.out.format(
                "search(\"%s\") -> \"%s\"%n", word, trie.search(word));

        test.accept("");
        test.accept(".");
        test.accept("..");
        test.accept("...");
        System.out.println();

        trie.addWord("abababababababababababababababababababababababababab");
        trie.addWord("ababababababababababababababababababababababcdcdcdcd");
        test.accept( "ababababababababababababababababababababa..........d");
        test.accept( "ababababababababababababababababababababa.........ad");
    }
}
