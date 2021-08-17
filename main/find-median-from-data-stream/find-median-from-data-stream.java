class MedianFinder {
    public void addNum(final int num) {
        (_low.isEmpty() || num < _low.peek() ? _low : _high).add(num);
        rebalance();
    }

    public double findMedian() {
        switch (_low.size() - _high.size()) {
        case 0:
            // The number of values is even, so average the two medial values.
            // Since int is only 32-bit, converting to double before adding,
            // instead of after, is sufficient to prevent arithmetic overflow.
            return ((double)_low.peek() + (double)_high.peek()) / 2.0;

        case +1:
            return _low.peek(); // _low is bigger so it has the medial value

        case -1:
            return _high.peek(); // _high is bigger so it has the medial value

        default:
            throw new AssertionError("the balancing invariant was violated");
        }
    }

    private void rebalance() {
        switch (_low.size() - _high.size()) {
        case +2: // _low is too big relative to _high
            _high.add(_low.remove());
            break;

        case -2: // _high is too big relative to _low
            _low.add(_high.remove());
            break;

        default: // the queue cannot currently be made any more balanced
        }
    }

    // A maxheap to store the smaller values.
    private final Queue<Integer> _low =
            new PriorityQueue<>(Comparator.reverseOrder());

    // A minheap to store the larger values.
    private final Queue<Integer> _high = new PriorityQueue<>();
}

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */
