final class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;

    public TreeNode(int x) { val = x; }
}

class Solution {
    public TreeNode sortedArrayToBST(int[] nums) {
        return sortedArrayToBST(nums, 0, nums.length - 1);
    }

    private static TreeNode sortedArrayToBST(final int[] nums,
                                             final int left, final int right) {
        if (left > right) return null;

        final int mid = left + (right - left) / 2;

        return makeNode(nums[mid], sortedArrayToBST(nums, left, mid - 1),
                                   sortedArrayToBST(nums, mid + 1, right));
    }

    private static TreeNode makeNode(final int val, final TreeNode left,
                                                    final TreeNode right) {
        final TreeNode node = new TreeNode(val);
        node.left = left;
        node.right = right;
        return node;
    }
}

final class UnitTest {
    public static void main(final String[] args) {
        test();
        test(18);
        test(-10, -3, 0, 5, 9);
        test(10, 20, 30, 40, 50, 60);
        test(1, 2, 3, 4, 5, 6, 7, 8, 9);
    }

    private static void test(int... nums) {
        System.out.println(serialize(SOLUTION.sortedArrayToBST(nums)) + ".");
    }

    private static String serialize(final TreeNode root) {
        String ret = "";
        if (root != null) ret += root.val + "(" + serialize(root.left) + ")("
                                                + serialize(root.right) + ")";
        return ret;
    }

    private UnitTest() { throw new AssertionError(); }

    private static final Solution SOLUTION = new Solution();
}
