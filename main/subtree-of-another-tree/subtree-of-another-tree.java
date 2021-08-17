/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    private static final class Key {
        Key(final int val, final int leftId, final int rightId) {
            _val = val;
            _leftId = leftId;
            _rightId = rightId;
        }

        @Override
        public boolean equals(final Object obj) {
            // The Key class is a private implementation detail whose instances
            // will only ever be compared to one another, not other objects.
            final Key key = (Key)obj;

            return _val == key._val && _leftId == key._leftId
                                    && _rightId == key._rightId;
        }

        @Override
        public int hashCode() {
            return _val +  31 * _leftId + 31 * 31 * _rightId;
        }

        private final int _val, _leftId, _rightId;
    }

    public boolean isSubtree(final TreeNode s, final TreeNode t) {
        final int nullId = -1, noId = -2;
        final Map<Key, Integer> ids = new HashMap<>();

        final ToIntFunction<TreeNode> createIds = new ToIntFunction<TreeNode>() {
            @Override
            public int applyAsInt(final TreeNode root) {
                if (root == null) return nullId;

                final Key key = new Key(root.val, applyAsInt(root.left),
                                                  applyAsInt(root.right));

                return ids.computeIfAbsent(key, k -> ids.size());
            }
        };

        final ToIntFunction<TreeNode> getId = new ToIntFunction<TreeNode>() {
            @Override
            public int applyAsInt(final TreeNode root) {
                if (root == null) return nullId;

                final int leftId = applyAsInt(root.left);
                if (leftId == noId) return noId;

                final int rightId = applyAsInt(root.right);
                if (rightId == noId) return noId;

                final Key key = new Key(root.val, leftId, rightId);
                return ids.getOrDefault(key, noId);
            }
        };

        createIds.applyAsInt(s);
        return getId.applyAsInt(t) != noId;
    }
}
