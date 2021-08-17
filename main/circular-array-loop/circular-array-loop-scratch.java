class Solution {
    private static int commonResidue(final int p, final int q) {
        // http://mathworld.wolfram.com/CommonResidue.html
        return (q + p % q) % q;
    }

    private static int next(final int[] nums, final int pos) {
        return commonResidue(pos + nums[pos], nums.length);
    }

    private static boolean tryLoop(final int[] nums, final boolean forward) {
        final int[] vis = new int[nums.length]; // visitation log by generation

        for (int gen = 1; gen <= nums.length; ++gen) {
            int pos = gen - 1;

            while ((nums[pos] > 0) == forward && vis[pos] == 0) {
                vis[pos] = gen;
                pos = next(nums, pos);
            }

            if (vis[pos] == gen && next(nums, pos) != pos) return true;
        }

        return false;
    }

    public boolean circularArrayLoop(final int[] nums) {
        return tryLoop(nums, true) || tryLoop(nums, false);
    }
}

final class UnitTest {
    private static void test(final int... nums) {
        System.out.println(new Solution().circularArrayLoop(nums));
    }

    public static void main(final String[] args) {
        test(-2, 1, -1, -2, -2);
        test(2, -1, -1);
        test(2, -1, 1, 2, 2);
        test(1, 1, 1, 1, 1, 1, 1);
        test(-1, -1, -1, -1, -1, -1, -1);
        test(1000);
        test(1001);
        test(1000, 1);
        test(1001, 1);
        test(1001, -1);
    }

    private UnitTest() { throw new AssertionError(); }
}
