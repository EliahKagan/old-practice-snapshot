using System;
using System.Collections.Generic;

internal sealed class MinHeap {
    public MinHeap() { _elems = new List<int>(); }
    public MinHeap(int capacity) { _elems = new List<int>(capacity); }

    public int Top => _elems[0];
    public int Count => _elems.Count;

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

        for (var current = 0; ;) {
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
        for (var current = _elems.Count - 1; current != 0;) {
            var parent = ParentIndexOf(current);
            if (_elems[parent] <= _elems[current]) break;
            Swap(current, parent);
            current = parent;
        }
    }
}

internal sealed class MaxHeap {
    public MaxHeap() { _elems = new List<int>(); }
    public MaxHeap(int capacity) { _elems = new List<int>(capacity); }

    public int Top => _elems[0];
    public int Count => _elems.Count;

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

        for (var current = 0; ;) {
            var left = LeftChildIndexOf(current);
            if (left >= size) break;

            var right = RightChildIndexOf(current);
            var child = (right < size && _elems[right] > _elems[left] ? right
                                                                      : left);
            if (_elems[current] > _elems[child]) break;

            Swap(current, child);
            current = child;
        }
    }

    private void HeapifyUp()
    {
        for (var current = _elems.Count - 1; current != 0;) {
            var parent = ParentIndexOf(current);
            if (_elems[parent] >= _elems[current]) break;
            Swap(current, parent);
            current = parent;
        }
    }
}

internal static class Solution {
    private static int Get() => int.Parse(Console.ReadLine());

    private static void Main()
    {
        const int extra = 8;

        var n = Get();
        var h = n / 2 + extra;
        var low = new MaxHeap(h);
        var high = new MinHeap(h);

        low.Add(Get());
        Console.WriteLine("{0:F1}", low.Top);

        while (--n != 0) {
            var e = Get();
            if (e < low.Top) low.Add(e);
            else high.Add(e);

            if (Math.Abs(low.Count - high.Count) > 1) {
                if (low.Count > high.Count) high.Add(low.Poll());
                else low.Add(high.Poll());
            }

            if (low.Count == high.Count) {
                var median = (low.Top + high.Top) / 2.0;
                Console.WriteLine("{0:F1}", median);
            } else {
                var median = (low.Count > high.Count ? low.Top : high.Top);
                Console.WriteLine("{0:F1}", median);
            }
        }
    }
}
