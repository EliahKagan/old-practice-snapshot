<Query Kind="Program" />

internal static class Algo {
    internal static void HeapSort<T>(this T[] keys) where T : IComparable<T>
    {
        var last = keys.Length - 1;
        if (last < 1) return;
        
        for (var i = 1; i != keys.Length; ++i) keys.HeapifyUp(i);
        
        for (var i = last; i != 0; --i) {
            keys.Swap(0, i);
            keys.HeapifyDown(i);
        }
    }
    
    private static void HeapifyUp<T>(this T[] keys, int start)
            where T : IComparable<T>
    {
        while (start != 0) {
            var parent = (start - 1) / 2;
            if (keys.OrderOK(parent, start)) break;
            keys.Swap(start, parent);
            start = parent;
        }
    }
    
    private static void HeapifyDown<T>(this T[] keys, int stop)
            where T : IComparable<T>
    {
        for (var start = 0; ; ) {
            var child = keys.PickChild(start, stop);
            if (child == -1 || keys.OrderOK(start, child)) break;
            keys.Swap(start, child);
            start = child;
        }
    }
    
    private static int PickChild<T>(this T[] keys, int start, int stop)
            where T : IComparable<T> // returns -1 if there are no children
    {
        var leftChild = start * 2 + 1;
        if (leftChild >= stop) return -1;
        
        var rightChild = leftChild + 1;
        
        return rightChild == stop || keys.OrderOK(leftChild, rightChild)
                ? leftChild
                : rightChild;
    }
    
    private static bool OrderOK<T>(this T[] keys, int i, int j)
            where T : IComparable<T>
        => keys[i].CompareTo(keys[j]) >= 0;
    
    private static void Swap<T>(this T[] keys, int i, int j)
    {
        var tmp = keys[i];
        keys[i] = keys[j];
        keys[j] = tmp;
    }
}

internal static class UnitTest {
    private static void Main()
    {
        var a = new[] { 10, 3, -1, 9, 56, 4, 22, 11, 10, 10, 14, -15, -2, -1, -8, 34, 33, 35, -16 };
        a.HeapSort();
        a.Dump();
        
        var b = new int[] { };
        b.HeapSort();
        b.Dump();
        
        var c = new[] { 3 };
        c.HeapSort();
        c.Dump();
        
        var d = new[] { "foo", "bar", "baz", "quux", "Washington", "foobar", "Michigan" };
        d.OrderBy(s => s).Dump();
        d.HeapSort();
        d.Dump();
    }
}
