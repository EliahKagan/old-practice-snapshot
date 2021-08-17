<Query Kind="Program">
  <Namespace>System.Diagnostics.Contracts</Namespace>
</Query>

// Counts pairs of integers in a that subtract to produce the value k.
private static int count_pairs(this int[] a, int n, int k) // note: mutates a
{
    Array.Sort(a);
    var count = 0;
    
    /*
    for (var i = 1; i < a.Length; ++i) {
        var cur = a[i - 1];
        var key = k - a[i - 1];
        if (key < 
        var j = Array.BinarySearch(a, i, a.Length - i, 
    }
    */
    
    var stop = n - 1;
    for (var i = 0; i < stop; ++i) {
        var key = k - a[i];
        if (key < a[i]) break;
        
        var j = Array.BinarySearch(a, i + 1, stop - i, key);
        if (j == -1) continue;
        
        ++count; // for a[i], a[j]
        for (var jj = j; --jj != i && a[jj] == key; ) ++count; // a[i], a[<j]
        while (++j != n && a[j] == key) ++count; // a[i], a[>j]
    }
    
    return count;
}