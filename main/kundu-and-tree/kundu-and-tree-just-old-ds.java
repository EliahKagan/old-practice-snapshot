import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.IntStream;

/** A disjoint-set-union data structure that tracks component sizes. */
final class DisjointSets {
    /**
     * Performs {@code count} makeset operations.
     * @param count  the number of singleton sets to create
     */
    DisjointSets(final int count) {
        _parents = new int[count];
        Arrays.setAll(_parents, elem -> elem);

        _sizes = new int[count];
        Arrays.fill(_sizes, 1);
    }

    /**
     * Finds the size of each component.
     * @return an array of the sizes, in descending order
     */
    int[] sizes() {
        return IntStream.range(0, _parents.length)
                .filter(elem -> elem == _parents[elem])
                .map(elem -> _sizes[elem])
                .map(x -> -x).sorted().map(x -> -x) // sort in descending order
                .toArray();
    }

    /**
     * Union by size with full path compression.
     * @param elem1  an element of the first set to participate in the union
     * @param elem2  an element of the second set to participate in the union
     */
    void union(int elem1, int elem2) {
        // Find the ancestors and stop if they are the same.
        elem1 = findSet(elem1);
        elem2 = findSet(elem2);
        if (elem1 == elem2) return;

        // Unite the sets by size.
        if (_sizes[elem1] < _sizes[elem2]) {
            join(elem2, elem1);
        } else {
            join(elem1, elem2);
        }
    }

    /**
     * Finds the ancestor, preforming full path compression.
     * @param elem  an element of the set whose representative is sought
     * @return the representative element of the set containing {@code index}
     */
    private int findSet(int elem) {
        // Find the ancestor.
        int leader = elem;
        while (leader != _parents[leader]) leader = _parents[leader];

        // Compress the path.
        while (elem != leader) {
            final int parent = _parents[elem];
            _parents[elem] = leader;
            elem = parent;
        }

        return leader;
    }

    /**
     * Joins the child to the parent.
     * @param parent  a set's representative that will present the new set
     * @param child  a set's representative that will not represent the new set
     */
    private void join(final int parent, final int child) {
        _sizes[parent] += _sizes[child];
        _parents[child] = parent;
    }

    private final int[] _parents;
    private final int[] _sizes;
}
