/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * public interface NestedInteger {
 *
 *     // @return true if this NestedInteger holds a single integer, rather than a nested list.
 *     public boolean isInteger();
 *
 *     // @return the single integer that this NestedInteger holds, if it holds a single integer
 *     // Return null if this NestedInteger holds a nested list
 *     public Integer getInteger();
 *
 *     // @return the nested list that this NestedInteger holds, if it holds a nested list
 *     // Return null if this NestedInteger holds a single integer
 *     public List<NestedInteger> getList();
 * }
 */

import java.util.NoSuchElementException;

public class NestedIterator implements Iterator<Integer> {
    public NestedIterator(final List<NestedInteger> nestedList) {
        _stack.push(nestedList.iterator());
    }

    @Override
    public Integer next() {
        if (!hasNext()) throw new NoSuchElementException();

        final Integer ret = _next;
        _next = null;
        return ret;
    }

    @Override
    public boolean hasNext() {
        if (_next != null) return true;

        while (!_stack.isEmpty()) {
            final Iterator<NestedInteger> it = _stack.element();

            if (!it.hasNext()) {
                _stack.pop();
                continue;
            }

            final NestedInteger ni = it.next();

            if (ni.isInteger()) {
                _next = ni.getInteger();
                return true;
            }

            _stack.push(ni.getList().iterator());
        }

        return false;
    }

    private final Deque<Iterator<NestedInteger>> _stack = new ArrayDeque<>();
    private Integer _next = null;

}

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i = new NestedIterator(nestedList);
 * while (i.hasNext()) v[f()] = i.next();
 */
