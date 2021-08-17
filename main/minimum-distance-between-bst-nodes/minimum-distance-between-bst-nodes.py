# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    @staticmethod
    def minDiffInBST(root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def dfs(node):
            if node is not None:
                yield from dfs(node.left)
                yield node.val
                yield from dfs(node.right)

        min_delta = math.inf

        prev = -math.inf
        for cur in dfs(root):
            min_delta = min(min_delta, cur - prev)
            prev = cur

        return min_delta
