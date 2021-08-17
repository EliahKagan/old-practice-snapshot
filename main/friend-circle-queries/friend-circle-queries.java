import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

/** A disjoint-set-union data structure that tracks component sizes. */
final class DisjointSets {
    /**
     * Creates a new singleton set.
     * @return the element index
     */
    int makeSet() {
        _elems.add(-1);
        return _elems.size() - 1;
    }

    /**
     * Unites the sets (union by size).
     * <p>If the elements start out in the same set, no new union happens.</p>
     * @param index1 an element of the first set to participate in the union
     * @param index2 an element of the second set to participate in the union
     * @return the size of the resulting set
     */
    int union(int index1, int index2) {
        // Find the ancestors and stop if they are the same.
        index1 = findSet(index1);
        index2 = findSet(index2);
        if (index1 == index2) return -_elems.get(index1);

        // Unite by size. Sizes are stored negatively, so the index with the
        // more negative associated value will be the parent. If there is a
        // tie, pick index1 as the parent (either could be used in that case).
        return _elems.get(index2) < _elems.get(index1) ? join(index2, index1)
                                                       : join(index1, index2);
    }

    /**
     * Finds the ancestor, performing full path compression.
     * @param index an element of the set whose representative is sought
     * @return the representative element of the set containing {@code index}
     */
    private int findSet(int index) {
        // Find the ancestor.
        int leader = index;
        while (_elems.get(leader) >= 0) leader = _elems.get(leader);

        // Compress the path.
        while (index != leader) {
            final int parent = _elems.get(index);
            _elems.set(index, leader);
            index = parent;
        }

        return leader;
    }

    /**
     * Joins the child to the parent.
     * @param parent a set's representative that will represent the new set
     * @param child a set's representative that will not represent the new set
     * @return the size of the new set
     */
    private int join(final int parent, final int child) {
        _elems.set(parent, _elems.get(parent) + _elems.get(child));
        _elems.set(child, parent);
        return -_elems.get(parent);
    }

    /**
     * When {@code i} is a representative element, {@code _elems[i]} is the
     * negative size of the set containing {@code i}. Otherwise,
     * {@code _elems[i]} is the parent of {@code i}.
     */
    private final List<Integer> _elems = new ArrayList<>();
}

/**
 * Wraps {@code DisjointSets} for an arbitrary key type {@code K}.
 * @param <K> the key type
 */
final class KeyedDisjointSets<K> {
    /**
     * Unites the sets containing {@code key1} and {@code key2}.
     * <p>If a key is not yet an element, a makeset operation is first
     * performed to create a singleton set containing that key.</p>
     * @param key1 an element key of the first set to participate in the union
     * @param key2 an element key of the second set to participate in the union
     * @return the size of the resulting set
     */
    int union(final K key1, final K key2) {
        return _sets.union(index(key1), index(key2));
    }

    /**
     * Obtains or creates the index for the specified key.
     * @param key the key to look up and make a singleton set for if necessary
     * @return the {@code DisjointSets} index corresponding to {@code key}
     */
    private int index(final K key) {
        return _map.computeIfAbsent(key, k -> _sets.makeSet());
    }

    private final Map<K, Integer> _map = new HashMap<>();
    private final DisjointSets _sets = new DisjointSets();
}

final class Solution {
    /**
     * Entry point function. Reads and solves one instance of the problem.
     * @param args Any command-line arguments are ignored.
     */
    public static void main(final String[] args) {
        final KeyedDisjointSets<Integer> ksets = new KeyedDisjointSets<>();
        int maxSize = 0;

        try (final Scanner sc = new Scanner(System.in)) {
            for (int queryCount = sc.nextInt(); queryCount > 0; --queryCount) {
                final int key1 = sc.nextInt(), key2 = sc.nextInt();
                maxSize = Math.max(maxSize, ksets.union(key1, key2));
                System.out.println(maxSize);
            }
        }
    }

    /** The {@code Solution} class should not be instantiated. */
    private Solution() {
        throw new AssertionError();
    }
}
