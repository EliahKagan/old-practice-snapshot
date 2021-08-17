using System;
using System.Collections.Generic;
using System.Linq;

internal sealed class MinHeap {
    public MinHeap() { _elems = new List<int>(); }
    public MinHeap(int capacity) { _elems = new List<int>(capacity); }

    public int Peek() => _elems[0];

    public int Poll()
    {
        int ret = _elems[0];

        var last = _elems.Count - 1;
        _elems[0] = _elems[last];
        _elems.RemoveAt(last);
        HeapifyDown();

        return ret;
    }

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

    private void HeapifyDown()
    {
        var size = _elems.Count;

        for (var current = 0; ; ) {
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
}

internal static class Solution {
    private static void Main()
    {
        var nk = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        var n = nk[0];
        var k = nk[1];

        var heap = new MinHeap(n);
        foreach (var s in Console.ReadLine().Split().Select(int.Parse))
            heap.Add(s);

        var count = 0;
        var stop = n - 1;
        for (; count != stop && heap.Peek() < k; ++count) {
            var s1 = heap.Poll();
            var s2 = heap.Poll();
            heap.Add(s1 + s2 * 2);
        }

        Console.WriteLine(count == stop && heap.Peek() < k ? -1 : count);
    }
}
