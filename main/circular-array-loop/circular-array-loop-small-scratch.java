import java.util.function.IntPredicate;

class Solution {
    // Only these filters should be passed to tryLoop(int[], IntPredicate).
    private static final IntPredicate REQUIRE_POSITIVE = x -> x > 0;
    private static final IntPredicate REQUIRE_NEGATIVE = x -> x < 0;

    private static int commonResidue(final int p, final int q) {
        // http://mathworld.wolfram.com/CommonResidue.html
        return (q + p % q) % q;
    }

    private static int lead(final int[] nums, final int pos) {
        // While leading, values must be replaced with their negations, so the
        // current traversal can tell that it visited them.
        final int next_pos = commonResidue(pos + nums[pos], nums.length);
        nums[pos] = -nums[pos];
        return next_pos;
    }

    private static int follow(final int[] nums, final int pos) {
        // While following, values must be negated to interpret them as deltas,
        // and must then be zeroed so the next traversal can tell that they
        // were visited in a previous traversal.
        final int next_pos = commonResidue(pos - nums[pos], nums.length);
        nums[pos] = 0;
        return next_pos;
    }

    private static boolean tryLoop(final int[] nums,
                                   final IntPredicate filter) {
        for (int start = 0; start != nums.length; ++start) {
            int moves = 0;

            // The leader traces out a path that ends either at a position
            // in the same path, which is the start of a cycle, or at a
            // position with an ineligible sign (as determined by filter).
            int leader = start;
            while (filter.test(nums[leader])) {
                leader = lead(nums, leader);
                ++moves;
            }

            // The follower zeros out elements at positions up to but not
            // including the leader's final position.
            int follower = start;
            while (follower != leader) {
                follower = follow(nums, follower);
                --moves;
            }

            // FIXME!! - Something is wrong here.
            // If that "failed" to retrace all the leader's steps, then a cycle
            // of order > 1, which is what we are looking for, was found.
            if (moves == 0) return true;

            // FIXME!! - Something is wrong here.
            // Otherwise, we've hit an unusable position (originally wrong sign
            // or zeroed out in a previous traversal). Zero out the rest of the
            // path until the leader is encountered again.
            assert moves > 0;
            while (moves != 0) {
                follower = follow(nums, follower);
                --moves;
            }
        }

        return false;
    }

    public boolean circularArrayLoop(final int[] nums) {
        return tryLoop(nums, REQUIRE_POSITIVE)
                || tryLoop(nums, REQUIRE_NEGATIVE);
    }
}

final class UnitTest {
    private static void test(final int... nums) {
        System.out.println(new Solution().circularArrayLoop(nums));
    }

    public static void main(final String[] args) {
        test(2, -1, -1);
        /*
        test(2, -1, 1, 2, 2);
        test(1, 1, 1, 1, 1, 1, 1);
        test(-1, -1, -1, -1, -1, -1, -1);
        test(1000);
        test(1001);
        test(1000, 1);
        test(1001, 1);
        test(1001, -1);
        */
    }

    private UnitTest() { throw new AssertionError(); }
}