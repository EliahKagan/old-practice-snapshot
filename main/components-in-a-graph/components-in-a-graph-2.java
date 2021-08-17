import java.util.Arrays;
import java.util.Scanner;

final class MinMaxPair {
    MinMaxPair(final int min, final int max) {
        this.min = min;
        this.max = max;
    }

    @Override
    public String toString() { return min + " " + max; }

    private final int min, max;
}

final class DisjointSets {
    DisjointSets(final int size) {
        _elems = new int[size];
        Arrays.fill(_elems, -1);
    }

    MinMaxPair computeComponentSizeRange() {
        int lower = 0, upper = Integer.MIN_VALUE;

        for (final int elem : _elems) {
            // Comparing to -1 instead of 0 disregards unconnected nodes.
            // Note that if we _did_ want to include unconnected nodes, then
            // consumers could not achieve 1-based indexing by creating an
            // extra node and attempting to ignore the node at index 0.
            if (elem < -1) {
                lower = Math.min(lower, elem);
                upper = Math.max(upper, elem);
            }
        }

        return new MinMaxPair(-upper, -lower);
    }

    void union(int i, int j) {   // union by size
        i = findSet(i);
        j = findSet(j);
        if (i == j) return;

        if (_elems[i] > _elems[j]) {    // _elems[j] is more negative
            _elems[j] += _elems[i];
            _elems[i] = j;
        } else {                        // _elems[i] is more negative
            _elems[i] += _elems[j];
            _elems[j] = i;
        }
    }

    private int findSet(int i) {    // find root, with full path compression
        int j = i;
        while (_elems[j] >= 0) j = _elems[j];

        while (i != j) { // path compression
            final int parent = _elems[i];
            _elems[i] = j;
            i = parent;
        }

        return j;
    }

    private final int[] _elems;
}

final class Solution {
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            // determine how many disjoint sets we will start with
            int n = sc.nextInt();
            final int size = n * 2 + 1;

            // make the disjoint sets and perform unions as directed by input
            final DisjointSets sets = new DisjointSets(size);
            while (n-- > 0) sets.union(sc.nextInt(), sc.nextInt());

            // compute and report the minimum and maximum component sizes
            System.out.println(sets.computeComponentSizeRange());
        }
    }

    private Solution() { throw new AssertionError(); }
}
