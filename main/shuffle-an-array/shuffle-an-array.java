import java.util.concurrent.ThreadLocalRandom;

class Solution {
    public Solution(final int[] nums) {
        _current = nums;

        _backup = new int[_current.length];
        copy(_current, _backup);
    }

    /** Resets the array to its original configuration and return it. */
    public int[] reset() {
        copy(_backup, _current);
        return _current;
    }

    /** Returns a random shuffling of the array. */
    public int[] shuffle() {
        final ThreadLocalRandom gen = ThreadLocalRandom.current();

        // shrink the unshuffled portion of the array, one element at a time
        for (int size = _current.length; size > 1; ) {
            final int pos = gen.nextInt(size);
            swap(pos, --size);
        }

        return _current;
    }

    /** Copies an array to another of the same size. Helper function for reset(). */
    private static void copy(final int[] src, final int[] dest) {
        if (src.length != dest.length)
            throw new IllegalArgumentException("arrays differ in size");

        System.arraycopy(src, 0, dest, 0, src.length);
    }

    /** Swaps the items at two indices. Helper function for shuffle(). */
    private void swap(final int i, final int j) {
        final int tmp = _current[i];
        _current[i] = _current[j];
        _current[j] = tmp;
    }

    private final int[] _current, _backup;
}

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int[] param_1 = obj.reset();
 * int[] param_2 = obj.shuffle();
 */
