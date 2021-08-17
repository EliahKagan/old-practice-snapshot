<Query Kind="Program">
  <Namespace>System.Diagnostics.Contracts</Namespace>
</Query>

// Counts pairs of integers in a that subtract to produce the value k.
private static int CountPairs(int[] a, int k) // note: mutates a
{
    Array.Sort(a);
    var count = 0;
    
    var stop = a.Length - 1;
    for (var i = 0; i < stop; ++i) {
        if (Array.BinarySearch(a, i + 1, stop - i, a[i] + k) >= 0)
            ++count;
    }
    
    return count;
}

private static void Main()
{
    CountPairs(new[] { 1, 5, 3, 4, 2 }, 2).Dump();
}