class Solution {
    public int[] smallestRange(final List<List<Integer>> nums) {
        int start = 0, stop = Integer.MAX_VALUE;
        final AndCounter targets = new AndCounter(nums.size());
        final MergingQueue merger = new MergingQueue(nums);

        for (int leftValue = start, rightValue = stop; ; ) {
            while (!targets.atGoal() && merger.canEnqueue()) {
                final Element elem = merger.enqueue();
                rightValue = elem.value;
                targets.add(elem.rowId);
            }

            if (!targets.atGoal()) break;

            while (targets.atGoal()) {
                final Element elem = merger.dequeue();
                leftValue = elem.value;
                targets.remove(elem.rowId);
            }

            if (rightValue - leftValue < stop - start) {
                start = leftValue;
                stop = rightValue;
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

/** Maintains a queue into which already-sorted rows are merged in order. */
class MergingQueue {
    MergingQueue(final List<List<Integer>> rows) {
        _iterators = new ArrayList<>(rows.size());
        for (final List<Integer> row : rows) _iterators.add(row.iterator());

        _heap = new PriorityQueue<>(rows.size());
        for (int rowId = 0; rowId != rows.size(); ++rowId) acquire(rowId);

        _fifo = new ArrayDeque<>();
    }

    /** Tells if it is still possible to expand the FIFO rightward. */
    boolean canEnqueue() {
        return !_heap.isEmpty();
    }

    /** Expands the FIFO rightward and returns the newly added pair. */
    Element enqueue() {
        final Element elem = dispense();
        _fifo.add(elem);
        return elem;
    }

    /** Contracts the FIFO leftward and returns the newly removed pair. */
    Element dequeue() {
        return _fifo.remove();
    }

    private void acquire(final int rowId) {
        final Iterator<Integer> it = _iterators.get(rowId);
        if (it.hasNext()) _heap.add(new Element(it.next(), rowId));
    }

    private Element dispense() {
        final Element elem = _heap.remove();
        acquire(elem.rowId);
        return elem;
    }

    private final List<Iterator<Integer>> _iterators;
    private final Queue<Element> _heap, _fifo;
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
