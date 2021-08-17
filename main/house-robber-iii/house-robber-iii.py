# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def rob(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        return self._rob(root, False)

    def _rob(self, root, must_skip):
        if root is None:
            return 0

        skip_sum = self._rob(root.left, False) + self._rob(root.right, False)
        if must_skip:
            return skip_sum

        noskip_sum = root.val + self._rob(root.left, True) + self._rob(root.right, True)
        return max(skip_sum, noskip_sum)
