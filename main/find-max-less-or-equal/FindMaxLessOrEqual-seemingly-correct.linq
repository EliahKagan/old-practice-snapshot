<Query Kind="Program">
  <Namespace>static System.Console</Namespace>
  <Namespace>static System.Linq.Enumerable</Namespace>
</Query>

internal static class ListEx {
    private static int FindMaxLessOrEqual(this List<long> seq, long key,
                                          int from, int to)
    {
        if (to < from) return to;

        var i = from + (to - from) / 2;

        if (key < seq[i]) return FindMaxLessOrEqual(seq, key, from, i - 1);
        if (key > seq[i]) return FindMaxLessOrEqual(seq, key, i + 1, to);
        return i;
    }

    // Returns the index of the last element of a not greater than n.
    // Assumes a is strictly increasing and contains such an element.
    internal static int FindMaxLessOrEqual(this List<long> seq, long key)
            => FindMaxLessOrEqual(seq, key, 0, seq.Count - 1);
}

internal static class UnitTest {
    private static void Main()
    {
        var a = Range(0, 1000000).Select(n => (long)(n * 3)).ToList();
        
        Range(0, 50)
            .Select(Key => new { Key, Index = a.FindMaxLessOrEqual(Key) })
            .Select(ki => new { ki.Key, Value = a[ki.Index], ki.Index })
            .Dump();
        
        // Further tests could go here.
    }
}