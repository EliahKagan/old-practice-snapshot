import java.util.ConcurrentModificationException;

class Solution {
    public int[] smallestRange(final List<List<Integer>> nums) {
        final Element[] elems = flatten(nums);
        Arrays.sort(elems);
        return findMinRangeCoveringAllGroups(elems, nums.size());
    }

    private static Element[] flatten(final List<List<Integer>> nums) {
        final Element[] elems = new Element[getTotalLength(nums)];

        int k = 0;
        for (int rowId = 0; rowId != nums.size(); ++rowId) {
            for (final int value : nums.get(rowId))
                elems[k++] = new Element(value, rowId);
        }

        if (k != elems.length) throw new ConcurrentModificationException();
        return elems;
    }

    private static <T> int getTotalLength(final List<List<T>> rows) {
        int len = 0;
        for (final List<T> row : rows) len += row.size();
        return len;
    }

    private static int[] findMinRangeCoveringAllGroups(final Element[] elems,
                                                       final int rowCount) {
        int start = elems[0].value, stop = elems[elems.length - 1].value;
        final AndCounter targets = new AndCounter(rowCount);

        for (int left = -1, right = -1; ; ) {
            while (!targets.atGoal() && ++right != elems.length)
                targets.add(elems[right].rowId);

            if (right == elems.length) break;

            while (targets.atGoal())
                targets.remove(elems[++left].rowId);

            if (elems[right].value - elems[left].value < stop - start) {
                start = elems[left].value;
                stop = elems[right].value;
            }
        }

        return new int[] { start, stop };
    }
}

/** A value that remembers what row it came from. */
final class Element implements Comparable<Element> {
    Element(final int value, final int rowId) {
        this.value = value;
        this.rowId = rowId;
    }

    public int compareTo(final Element other) {
        return Integer.compare(value, other.value);
    }

    final int value, rowId;
}

/** Tracks frequencies of items and knows if it has at least one of each. */
final class AndCounter {
    AndCounter(final int size) {
        _counts = new int[size];
        _missing = size;
    }

    void add(final int item) {
        if (_counts[item]++ == 0) --_missing;
    }

    void remove(final int item) {
        if (--_counts[item] == 0) ++_missing;
    }

    boolean atGoal() {
        return _missing == 0;
    }

    private final int[] _counts;

    private int _missing;
}
