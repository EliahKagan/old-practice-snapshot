# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

import contextlib

class Solution:
    @staticmethod
    def findSecondMinimumValue(root):
        """
        :type root: TreeNode
        :rtype: int
        """
        with contextlib.suppress(StopIteration):
            it = Solution._dfs(root)
            x = next(it)

            while True:
                y = next(it)
                if y != x:
                    return y

        return -1

    @staticmethod
    def _dfs(root):
        if root is not None:
            yield from Solution._dfs(root.left)
            yield root.val
            yield from Solution._dfs(root.right)
