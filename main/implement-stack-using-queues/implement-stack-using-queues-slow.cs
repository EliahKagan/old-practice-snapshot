public class MyStack {
    /** Push element x onto stack. */
    public void Push(int x) {
        var n = _elems.Count;
        _elems.Enqueue(x);
        while (n-- != 0) _elems.Enqueue(_elems.Dequeue());
    }

    /** Removes the element on top of the stack and returns that element. */
    public int Pop() => _elems.Dequeue();

    /** Get the top element. */
    public int Top() => _elems.Peek();

    /** Returns whether the stack is empty. */
    public bool Empty() => _elems.Count == 0;

    private readonly Queue<int> _elems = new Queue<int>();
}

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack obj = new MyStack();
 * obj.Push(x);
 * int param_2 = obj.Pop();
 * int param_3 = obj.Top();
 * bool param_4 = obj.Empty();
 */
