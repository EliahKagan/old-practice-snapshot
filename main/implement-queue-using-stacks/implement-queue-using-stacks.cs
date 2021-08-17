public class MyQueue {
    /** Push element x to the back of queue. */
    public void Push(int x) => incoming.Push(x);

    /** Removes the element from in front of queue and returns that element. */
    public int Pop() {
        Recharge();
        return outgoing.Pop();
    }

    /** Get the front element. */
    public int Peek() {
        Recharge();
        return outgoing.Peek();
    }

    /** Returns whether the queue is empty. */
    public bool Empty() => incoming.Count == 0 && outgoing.Count == 0;

    private void Recharge() {
        if (outgoing.Count == 0)
            while (incoming.Count != 0) outgoing.Push(incoming.Pop());
    }

    private readonly Stack<int> incoming = new Stack<int>();
    private readonly Stack<int> outgoing = new Stack<int>();
}

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = new MyQueue();
 * obj.Push(x);
 * int param_2 = obj.Pop();
 * int param_3 = obj.Peek();
 * bool param_4 = obj.Empty();
 */
