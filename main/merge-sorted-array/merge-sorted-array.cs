public class Solution {
    public void Merge(int[] a, int m, int[] b, int n) {
        // Slide num1's elements out of the way.
        var i = m;
        var j = m + n;
        while (i != 0) a[--j] = a[--i];

        // Merge the elements from a and b into a.
        var k = 0;
        while (j != m + n && k != n) a[i++] = (a[j] < b[k] ? a[j++] : b[k++]);
        while (j != m + n) a[i++] = a[j++];
        while (k != n) a[i++] = b[k++];

        // Neither Debug.Assert nor Contract.Assert works on leetcode.com.
        if (i != m + n) throw new ArgumentOutOfRangeException();
    }
}
