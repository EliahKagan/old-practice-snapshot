using System;
using System.Collections.Generic;

[assembly: System.Reflection.AssemblyVersion("2.0.0.0")]

internal sealed class Heap<T> {
    public Heap(Comparison<T> comparison)
    {
        _comp = comparison;
        _elems = new List<T>();
    }

    public Heap(Comparison<T> comparison, int capacity)
    {
        _comp = comparison;
        _elems = new List<T>(capacity);
    }

    public T Top => _elems[0];

    public int Count => _elems.Count;

    public T Poll()
    {
        var ret = _elems[0];

        var last = _elems.Count - 1;
        _elems[0] = _elems[last];
        _elems.RemoveAt(last);
        HeapifyDown();

        return ret;
    }

    public void Add(T value)
    {
        _elems.Add(value);
        HeapifyUp();
    }

    private static int LeftChildIndexOf(int index) => index * 2 + 1;
    private static int RightChildIndexOf(int index) => index * 2 + 2;
    private static int ParentIndexOf(int index) => (index - 1) / 2;

    private readonly Comparison<T> _comp;
    private readonly List<T> _elems;

    private void Swap(int i, int j)
    {
        var tmp = _elems[i];
        _elems[i] = _elems[j];
        _elems[j] = tmp;
    }

    private bool Lt(int i, int j) => _comp(_elems[i], _elems[j]) < 0;
    private bool LtEq(int i, int j) => _comp(_elems[i], _elems[j]) <= 0;

    private void HeapifyDown()
    {
        var size = _elems.Count;

        for (var current = 0; ; ) {
            var left = LeftChildIndexOf(current);
            if (left >= size) break;

            var right = RightChildIndexOf(current);
            var child = (right < size && Lt(right, left) ? right : left);
            if (LtEq(current, child)) break;

            Swap(current, child);
            current = child;
        }
    }

    private void HeapifyUp()
    {
        for (var current = _elems.Count - 1; current != 0; ) {
            var parent = ParentIndexOf(current);
            if (LtEq(parent, current)) break;
            Swap(current, parent);
            current = parent;
        }
    }
}

internal static class Solution {
    private static int Get() => int.Parse(Console.ReadLine());
    private static void Put<T>(T e) => Console.WriteLine("{0:F1}", e);

    private static void Add(Heap<int> low, Heap<int> high, int e)
        => (e < low.Top ? low : high).Add(e);

    private static void Rebalance(Heap<int> low, Heap<int> high)
    {
        if (Math.Abs(low.Count - high.Count) == 2) {
            if (low.Count > high.Count) high.Add(low.Poll());
            else low.Add(high.Poll());
        }
    }

    private static double ComputeMedian(Heap<int> low, Heap<int> high)
        => low.Count == high.Count
                ? (low.Top + high.Top) / 2.0
                : (low.Count > high.Count ? low : high).Top;

    private static void Main()
    {
        const int extra = 8;

        var n = Get();
        var h = n / 2 + extra;
        var low = new Heap<int>((x, y) => y - x, h); // max-heap
        var high = new Heap<int>((x, y) => x - y, h); // min-heap

        low.Add(Get());
        Put(low.Top);

        while (--n != 0) {
            Add(low, high, Get());
            Rebalance(low, high);
            Put(ComputeMedian(low, high));
        }
    }
}
