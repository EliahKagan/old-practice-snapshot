class Solution {
    private static int commonResidue(final int p, final int q) {
        // http://mathworld.wolfram.com/CommonResidue.html
        return (q + p % q) % q;
    }

    private static int next(final int[] nums, final int pos) {
        return commonResidue(pos + nums[pos], nums.length);
    }

    private static boolean valid(final int[] nums, final boolean forward,
                                 final int pos) {
        return forward ? nums[pos] > 0 : nums[pos] < 0;
    }

    private static void erasePath(final int[] nums, int startInclusive,
                                                    final int endExclusive) {
        while (startInclusive != endExclusive) {
            final int prev = startInclusive;
            startInclusive = next(nums, startInclusive);
            nums[prev] = 0;
        }
    }

    private static boolean tryPath(final int[] nums, final boolean forward,
                                   final int start) {
        // Tortoise and hare algorithm.
        int slow = start, fast = start;
        boolean foundCycle = false;

        while (valid(nums, forward, fast)) {
            // fast advances by two and checks for the end of the path
            fast = next(nums, fast);
            if (!valid(nums, forward, fast)) break;
            fast = next(nums, fast);

            // slow advances by one and checks for overlap with fast
            slow = next(nums, slow);
            if (slow == fast) {
                foundCycle = true;
                break;
            }
        }

        if (foundCycle) {
            //System.err.format("Found cycle at position %d.\n", fast);
            if (fast != next(nums, fast)) return true; // not a singleton, yay!
            nums[fast] = 0;
        }

        erasePath(nums, start, fast);
        return false;
    }

    private static boolean findCycle(final int[] nums, final boolean forward) {
         for (int start = 0; start != nums.length; ++start)
             if (tryPath(nums, forward, start)) return true;

         return false;
    }

    public boolean circularArrayLoop(final int[] nums) {
        return findCycle(nums, true) || findCycle(nums, false);
    }
}
