// See http://cstheory.stackexchange.com/a/2589 for algorithm explanation
// (author: http://cstheory.stackexchange.com/users/988/alex-ten-brink).
// This is that same algorithm, but I have not copied any actual code.

public class MyStack {
    /** Push element x onto stack. */
    public void Push(int x) {
        // Add to the upper queue and rotate to the front.
        _upper.Enqueue(x);
        for (var i = _upper.Count; i != 1; --i)
            _upper.Enqueue(_upper.Dequeue());

        // Keep the upper queue small.
        if (_upper.Count * _upper.Count > _lower.Count) {
            while (_lower.Count != 0) _upper.Enqueue(_lower.Dequeue());
            SwapQueues();
        }
    }

    /** Removes the element on top of the stack and returns that element. */
    public int Pop()
        => _upper.Count != 0 ? _upper.Dequeue() : _lower.Dequeue();

    /** Get the top element. */
    public int Top()
        => _upper.Count != 0 ? _upper.Peek() : _lower.Peek();

    /** Returns whether the stack is empty. */
    public bool Empty()
        => _upper.Count == 0 && _lower.Count == 0;

    private void SwapQueues() {
        var tmp = _upper;
        _upper = _lower;
        _lower = tmp;
    }

    private Queue<int> _upper = new Queue<int>(), _lower = new Queue<int>();
}

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack obj = new MyStack();
 * obj.Push(x);
 * int param_2 = obj.Pop();
 * int param_3 = obj.Top();
 * bool param_4 = obj.Empty();
 */
