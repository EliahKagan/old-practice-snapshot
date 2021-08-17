using System;
using System.Collections.Generic;

internal sealed class MinHeap {
    public MinHeap() { _elems = new List<int>(); }
    public MinHeap(int capacity) { _elems = new List<int>(capacity); }

    public int Peek() => _elems[0];

    public int Poll() => PollAt(0);
    public int Poll(int value) => PollAt(_elems.IndexOf(value));

    public void Add(int value)
    {
        _elems.Add(value);
        HeapifyUp();
    }

    private readonly List<int> _elems;

    private static int LeftChildIndexOf(int index) => index * 2 + 1;
    private static int RightChildIndexOf(int index) => index * 2 + 2;
    private static int ParentIndexOf(int index) => (index - 1) / 2;

    private void Swap(int i, int j)
    {
        var tmp = _elems[i];
        _elems[i] = _elems[j];
        _elems[j] = tmp;
    }

    private void HeapifyDown(int current = 0)
    {
        for (var size = _elems.Count; ; ) {
            var left = LeftChildIndexOf(current);
            if (left >= size) break;

            var right = RightChildIndexOf(current);
            var child = (right < size && _elems[right] < _elems[left] ? right
                                                                      : left);
            if (_elems[current] < _elems[child]) break;

            Swap(current, child);
            current = child;
        }
    }

    private void HeapifyUp()
    {
        for (var current = _elems.Count - 1; current != 0; ) {
            var parent = ParentIndexOf(current);
            if (_elems[parent] <= _elems[current]) break;
            Swap(current, parent);
            current = parent;
        }
    }

    private int PollAt(int current)
    {
        int ret = _elems[current];

        var last = _elems.Count - 1;
        _elems[current] = _elems[last];
        _elems.RemoveAt(last);
        HeapifyDown(current);

        return ret;
    }
}

internal static class Solution {
    private static void Main()
    {
        var heap = new MinHeap(100000);

        for (var q = int.Parse(Console.ReadLine()); q > 0; --q) {
            var a = Array.ConvertAll(Console.ReadLine().Trim().Split(),
                                     int.Parse);

            switch (a[0]) {
            case 1:
                heap.Add(a[1]);
                break;

            case 2:
                heap.Poll(a[1]);
                break;

            case 3:
                Console.WriteLine(heap.Peek());
                break;

            default:
                throw new ArgumentOutOfRangeException();
            }
        }
    }
}
