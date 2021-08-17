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
     * Gets the sum of the sizes of all sets.
     * <p>This is a constant-time operation.</p>
     * @return the total number of elements in all sets
     */
    int count() {
        return _parents.length;
    }

    /**
     * Yields the size of each component.
     * @return a stream of the sizes
     */
    IntStream sizes() {
        return IntStream.range(0, _parents.length)
                .filter(elem -> elem == _parents[elem])
                .map(elem -> _sizes[elem]);
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
     * @param parent  a set's representative that will represent the new set
     * @param child  a set's representative that will not represent the new set
     */
    private void join(final int parent, final int child) {
        _sizes[parent] += _sizes[child];
        _parents[child] = parent;
    }

    private final int[] _parents;
    private final int[] _sizes;
}

final class Solution {
    /**
     * Entry point.
     * @param args  any command-line arguments are unused
     */
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            int n = sc.nextInt();

            // We have n vertices, but use n + 1 elements for 1-based indexing.
            final DisjointSets sets = new DisjointSets(n + 1);

            while (--n > 0) { // A tree has one fewer edge than vertices.
                final int elem1 = sc.nextInt(), elem2 = sc.nextInt();
                final String color = sc.next();

                if (color.equals("r")) continue; // red

                if (!color.equals("b")) // neither red nor black
                    throw new IllegalStateException("invalid color");

                sets.union(elem1, elem2); // black
            }

            System.out.println(countTriplets(sets));
        }
    }

    /**
     * Computes the number of unordered triplets of elements each drawn from a
     * different disjoint set.
     * @param sets  the disjoints from which elements will be picked
     * @return  the number of triplets, modulo {@code MOD}
     */
    private static long countTriplets(final DisjointSets sets) {
        long itemsTotal = sets.count() - 1;
        final int[] itemCounts = sets.sizes().skip(1).toArray();

        final long[] pairCounts = new long[itemCounts.length];
        long pairsTotal = 0L;
        for (int i = 0; i != itemCounts.length; ++i) {
            pairCounts[i] = itemCounts[i] * (itemsTotal -= itemCounts[i]);
            pairsTotal += pairCounts[i];
        }

        long tripletsTotal = 0L;
        for (int i = 0; i != pairCounts.length; ++i) {
            tripletsTotal += itemCounts[i] * (pairsTotal -= pairCounts[i]);
            tripletsTotal %= MOD;
        }

        return tripletsTotal;
    }

    /** Triplet counts will be computed modulo this number. */
    private static final long MOD = 1_000_000_007L;

    /** The {@code Solution} class should not be instantiated. */
    private Solution() {
        throw new AssertionError();
    }
}
