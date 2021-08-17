<Query Kind="Program" />

internal static class Hoare {
    private static void Swap<T>(this IList<T> a, int i, int j)
    {
        var tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
    
    private static int Partition<T>(this IList<T> a, int low, int high)
        where T : IComparable<T>
    {
        var pivot = a[low];
        var left = low - 1;
        var right = high + 1;
        
        for (; ; ) {
            while (a[++left].CompareTo(pivot) < 0) { }
            while (a[--right].CompareTo(pivot) > 0) { }
            if (left >= right) {
                (right - left).Dump("right - left");
                return right;
            }
            a.Swap(left, right);
        }
    }
    
    private static void Quicksort<T>(this IList<T> a, int low, int high)
        where T : IComparable<T>
    {
        if (low < high) {
            var mid = a.Partition(low, high);
            a.Quicksort(low, mid);
            a.Quicksort(mid + 1, high);
        }
    }
    
    internal static void Quicksort<T>(this IList<T> a) where T : IComparable<T>
        => a.Quicksort(0, a.Count - 1);
}

internal static class UnitTest {
    private static void Test<T>(this IList<T> a) where T : IComparable<T>
    {
        a.Quicksort();
        a.Dump();
    }
    
    private static void Main()
    {
        new int[] { 111, 333, 222 }.Test();
        new int[] { 3, 7, 1, 5, 2, -6, 15, 4, 33, -5 }.Test();
        new int[] { 9, 9, 1, 8, 3, 0, 2, 0, 7, 15, 4, 3, 3 }.Test();
        new int[] { 2, 1 }.Test();
        new int[] { 1, 2 }.Test();
        new int[] { 5 }.Test();
        new int[] { }.Test();
    }
}