<Query Kind="Program" />

public static void Merge(int[] nums1, int m, int[] nums2, int n) {
    var dest = m + n - 1;
    var src1 = m - 1;
    var src2 = n - 1;
    
    while (0 <= src1 && 0 <= src2) {
        nums1[dest--] = (nums1[src1] > nums2[src2] ? nums1[src1--]
                                                   : nums2[src2--]);
    }
    
    while (0 <= src1) nums1[dest--] = nums1[src1--];
    while (0 <= src2) nums1[dest--] = nums2[src2--];
    
    // Neither Debug.Assert nor Contract.Assert works on leetcode.com.
    if (dest != -1) throw new ArgumentOutOfRangeException();
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
