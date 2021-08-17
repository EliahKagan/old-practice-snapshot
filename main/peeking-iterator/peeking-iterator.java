// Java Iterator interface reference:
// https://docs.oracle.com/javase/8/docs/api/java/util/Iterator.html
class PeekingIterator implements Iterator<Integer> {
    public PeekingIterator(final Iterator<Integer> iterator) {
        _iterator = iterator;
    }

    // Returns the next element in the iteration without advancing the iterator.
    public Integer peek() {
        if (!_peeked) {
            _next = _iterator.next();
            _peeked = true;
        }

        return _next;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    @Override
    public Integer next() {
        if (_peeked) {
            _peeked = false;
            return _next;
        }

        return _iterator.next();
    }

    @Override
    public boolean hasNext() {
        return _peeked || _iterator.hasNext();
    }

    private final Iterator<Integer> _iterator;

    private Integer _next;

    private boolean _peeked = false;
}
