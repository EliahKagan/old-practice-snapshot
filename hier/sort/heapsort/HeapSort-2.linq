<Query Kind="Program" />

internal static class Algo {
    internal static void HeapSort<T>(this IList<T> keys, Comparison<T> compare)
    {
        var stop = keys.Count;
        if (stop < 2) return;
    
        void Swap(int i, int j) {
            var tmp = keys[i];
            keys[i] = keys[j];
            keys[j] = tmp;
        }
        
        bool OrderOK(int i, int j) => compare(keys[i], keys[j]) >= 0;
        
        int PickChild(int start) { // at the lowest level, returns -1
            var leftChild = start * 2 + 1;
            if (leftChild >= stop) return -1;
            
            var rightChild = leftChild + 1;
            
            return rightChild == stop || OrderOK(leftChild, rightChild)
                    ? leftChild
                    : rightChild;
        }
        
        void HeapifyDown(int start) {
            for (; ; ) {
                var child = PickChild(start);
                if (child == -1 || OrderOK(start, child)) break;
                Swap(start, child);
                start = child;
            }
        }
        
        // Turn the array into a maxheap.
        for (var i = stop / 2; i != -1; --i) HeapifyDown(i);
        
        // Extract each element, placing them from right to left.
        while (--stop != 0) {
            Swap(0, stop);
            HeapifyDown(0);
        }
    }
    
    internal static void HeapSort<T>(this IList<T> keys)
        => keys.HeapSort(Comparer<T>.Default.Compare);
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
