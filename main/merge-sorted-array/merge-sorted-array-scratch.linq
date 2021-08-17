<Query Kind="Program" />

public static void Merge(int[] a, int m, int[] b, int n) {
    // Slide num1's elements out of the way.
    var i = m;
    var j = m + n;
    while (i != 0) a[--j] = a[--i];
    
    // Merge the elements from a and b into a.
    var k = 0;
    while (j != m + n && k != n) a[i++] = (a[j] < b[k] ? a[j++] : b[k++]);
    while (j != m + n) a[i++] = a[j++];
    while (k != n) a[i++] = b[k++];
    
    // Neither Debug.Assert and Contract.Assert don't works leetcode.com.
    if (i != m + n) throw new ArgumentOutOfRangeException();
}

private static void Test(int[] a, int[] b) {
    var m = a.Dump("old a (short)").Length;
    var n = b.Dump("b").Length;
    
    a = a.Concat(Enumerable.Repeat(-1, b.Length)).ToArray()
         .Dump("new a (long), before copying");
    
    Merge(a, m, b, n);
    a.Dump("new a (long), after copying");
}

private static void Main() {
    Test(new[] { 1, 2, 4 }, new[] { 2, 3, 4 });
    Test(new int[] { }, new int[] { });
    Test(new [] {1, 2, 3}, new int[] { });
    Test(new int [] { }, new[] {1, 2});
}
