# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def sumOfLeftLeaves(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        return self._dfs(root, False)

    def _dfs(self, root, left):
        if root is None:
            return 0
        if root.left is None and root.right is None:
            return root.val if left else 0
        return self._dfs(root.left, True) + self._dfs(root.right, False)
