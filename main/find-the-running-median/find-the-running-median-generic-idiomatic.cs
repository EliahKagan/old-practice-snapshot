using System;
using System.Collections.Generic;

[assembly: System.Reflection.AssemblyVersion("3.0.0.0")]

internal sealed class PriorityQueue<T> {
    public static PriorityQueue<T> CreateMinQueue() => new PriorityQueue<T>();
    
    public static PriorityQueue<T> CreateMaxQueue() =>
        new PriorityQueue<T>((x, y) => Comparer<T>.Default.Compare(y, x));

    public PriorityQueue(Comparison<T> compare) => _compare = compare;
    
    public PriorityQueue() : this(Comparer<T>.Default.Compare) { }
    
    public void Push(T value) {
        _elems.Add(value);
        HeapifyUp();
    }
    
    public T Peek() {
        try {
            return _elems[0];
        }
        catch (IndexOutOfRangeException e) {
            throw new InvalidOperationException("Priority queue empty.", e);
        }
    }
    
    public T Pop() {
        var ret = Peek();
        
        _elems[0] = _elems[Count - 1];
        _elems.RemoveAt(Count - 1);
        HeapifyDown();
        
        return ret;
    }
    
    public int Count => _elems.Count;
    
    private void HeapifyUp() {
        for (var current = Count - 1; current > 0; ) {
            var parent = (current - 1) / 2;
            if (OrderOK(parent, current)) break;
            Swap(parent, current);
            current = parent;
        }
    }
    
    private void HeapifyDown() {
        for (var current = 0; ; ) {
            var leftChild = current * 2 + 1;
            if (leftChild >= Count) break;
            
            var rightChild = leftChild + 1;
            
            var child = (rightChild == Count || OrderOK(leftChild, rightChild)
                            ? leftChild
                            : rightChild);
            
            if (OrderOK(current, child)) break;
            Swap(current, child);
            current = child;
        }
    }
    
    private bool OrderOK(int i, int j) => _compare(_elems[i], _elems[j]) <= 0;
    
    private void Swap(int i, int j) {
        var tmp = _elems[i];
        _elems[i] = _elems[j];
        _elems[j] = tmp;
    }
    
    private List<T> ToDump() => _elems;

    private readonly List<T> _elems = new List<T>();
    
    private readonly Comparison<T> _compare;
}

internal sealed class MedianFinder {
    public void AddNum(int num) {
        (_low.Count == 0 || num < _low.Peek() ? _low : _high).Push(num);
        Rebalance();
    }
    
    public double FindMedian() {
        switch (SizeDelta) {
        case 0:
            try {
                // Converting to double before adding instead of after prevents
                // arithmetic overflow.
                return ((double)_low.Peek() + (double)_high.Peek()) / 2.0;
            }
            catch (InvalidOperationException e) {
                throw new InvalidOperationException(
                        "Can't take the median of zero values.", e);
            }
        
        case +1:
            return _low.Peek();
        
        case -1:
            return _high.Peek();
        
        default:
            throw new NotSupportedException(
                    "internal error: balancing invariant somehow violated!");
        }
    }
    
    private void Rebalance() {
        switch (SizeDelta) {
        case +2:
            _high.Push(_low.Pop());
            break;
            
        case -2:
            _low.Push(_high.Pop());
            break;
        
        default:
            break; // the heaps can't be made any more balanced right now
        }
    }
    
    private int SizeDelta => _low.Count - _high.Count;
    
    private readonly PriorityQueue<int> _low =
            PriorityQueue<int>.CreateMaxQueue();
    
    private readonly PriorityQueue<int> _high =
            PriorityQueue<int>.CreateMinQueue();
}

internal static class Solution {
    private static void Main() {
        var finder = new MedianFinder();

        for (var n = ReadValue(); n > 0; --n) {
            finder.AddNum(ReadValue());
            Console.WriteLine("{0:F1}", finder.FindMedian());
        }
    }

    private static int ReadValue() => int.Parse(Console.ReadLine());
}
