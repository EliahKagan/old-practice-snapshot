public class MinStack {
    /** initialize your data structure here. */
    public MinStack() => _mins.Push(int.MaxValue);

    public void Push(int x) {
        _elems.Push(x);
        if (x <= _mins.Peek()) _mins.Push(x);
    }

    public void Pop() {
        if (_mins.Peek() == _elems.Pop()) _mins.Pop();
    }

    public int Top() => _elems.Peek();

    public int GetMin() => _mins.Peek();

    private readonly Stack<int> _elems = new Stack<int>();

    private readonly Stack<int> _mins = new Stack<int>();
}

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.Push(x);
 * obj.Pop();
 * int param_3 = obj.Top();
 * int param_4 = obj.GetMin();
 */
