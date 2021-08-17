<Query Kind="Program" />

// Returns the last index to an element less than or equal to key,
// in range a[low..high], or low if there is no such element.
private static int FindLastNotGreater(int[] a, int low, int high, int key)
{
    $"low: {low}, high: {high}".Dump();

    if (low >= high) return low;
    
    var mid = (low + high + 1) / 2;
    
    return a[mid] > key ? FindLastNotGreater(a, 0, mid - 1, key)
                        : FindLastNotGreater(a, mid, high, key);
}

// Returns the last index to an element less than or equal to key,
// or 0 if there is no such element.
private static int FindLastNotGreater(int[] a, int key)
    => FindLastNotGreater(a, 0, a.Length - 1, key);

private static void Main()
{
    var a = new[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4 };
    FindLastNotGreater(a, 3).Dump();
    
    var b = new [] { 20, 40, 50, 60 };
    FindLastNotGreater(b, 10).Dump();
    
    var c = new int[] { };
    FindLastNotGreater(c, 3).Dump();
    
    var d = new[] { 0, 1, 1, 1, 2, 4 };
    FindLastNotGreater(d, 1).Dump();
}