public class Solution {
    public int TrailingZeroes(int n)
        => CountFactors(n, 5);

    private static int CountFactors(int n, int k) {
        var count = 0;
        while (n > 0) count += (n /= k);
        return count;
    }
}
