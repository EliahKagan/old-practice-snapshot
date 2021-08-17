<Query Kind="Program">
  <Namespace>static System.Console</Namespace>
  <Namespace>static System.Linq.Enumerable</Namespace>
</Query>

internal static class ListEx {
    private static int LowerBound(this List<int> arr, int key,
                                   int low, int high)
    {
        if (high < low) return low;
        
        var mid = low + (high - low) / 2;
        
        return arr[mid] < key ? arr.LowerBound(key, mid + 1, high)
                              : arr.LowerBound(key, low, mid - 1);
    }
    
    internal static int LowerBound(this List<int> arr, int key)
            => arr.LowerBound(key, 0, arr.Count - 1);
}

internal static class UnitTest {
    private static void Main()
    {
        var a = Range(0, 1000000).Select(n => n * 3).ToList();
        
        Range(-10, 50)
            .Select(Key => new { Key, Index = a.LowerBound(Key) })
            .Select(ki => new { ki.Key, Value = a[ki.Index], ki.Index })
            .Dump();
        
        // Further tests could go here.
    }
}