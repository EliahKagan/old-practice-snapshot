<Query Kind="Program" />

internal static class Algo {
    internal static void Heapsort2<TKey, TVal>(this IList<TKey> keys,
            IList<TVal> values, Comparison<TKey> compare)
    {
        var len = keys.Count;
        
        if (len != values.Count) {
            throw new ArgumentException($"{nameof(values)} must have the same "
                                            + $"length as {nameof(keys)}",
                                        nameof(values));
        }
        
        if (len < 2) return;
    
        void Exchange<T>(IList<T> a, int i, int j) {
            var tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
        
        void Swap(int i, int j) {
            Exchange(keys, i, j);
            Exchange(values, i, j);
        }
        
        bool OrderOK(int i, int j) => compare(keys[i], keys[j]) >= 0;
        
        int PickChild(int start, int stop) { // gets left or right child or -1
            var left = start * 2 + 1;
            if (left >= stop) return -1;
            
            var right = left + 1;
            return right == stop || OrderOK(left, right) ? left : right;
        }
        
        void HeapifyDown(int start, int stop) {
            for (; ; ) {
                var child = PickChild(start, stop);
                if (child == -1 || OrderOK(start, child)) break;
                Swap(start, child);
                start = child;
            }
        }
        
        // Turn the data into a maxheap.
        for (var start = len / 2; start != -1; --start)
            HeapifyDown(start, len);
        
        // Extract each element, placing them right to left.
        for (var stop = len - 1; stop != 0; --stop) {
            Swap(0, stop);
            HeapifyDown(0, stop);
        }
    }
    
    internal static void Heapsort2<TKey, TVal>(this IList<TKey> keys,
                                               IList<TVal> values)
        => keys.Heapsort2(values, Comparer<TKey>.Default.Compare);
}

internal static class UnitTest {
    private static void Main()
    {
        Test(10, 3, -1, 9, 56, 4, 22, 11, 10, 10, 14, -15, -2, -1, -8, 34, 33, 35);
        Test("foo", "bar", "baz", "quux", "Washington", "foobar", "Michigan");
    }
    
    private static void Test<T>(params T[] a)
    {
        var w = a.DefaultIfEmpty().Max(e => e.ToString().Length);
        var b = Enumerable.Range(0, a.Length).ToArray();
        
        void Print() {
            Console.WriteLine();
            for (var i = 0; i != a.Length; ++i)
                Console.WriteLine($"{a[i].ToString().PadLeft(w)} {b[i],4}");
        }
        
        a.Heapsort2(b);
        Print();
        b.Heapsort2(a);
        Print();
    }
}
