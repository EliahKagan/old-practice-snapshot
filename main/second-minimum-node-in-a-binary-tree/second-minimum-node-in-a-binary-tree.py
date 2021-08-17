# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    @staticmethod
    def findSecondMinimumValue(root):
        """
        :type root: TreeNode
        :rtype: int
        """
        first = second = math.inf

        for val in Solution._dfs(root):
            if val < first:
                second = first
                first = val
            elif val != first and val < second:
                second = val

        return -1 if second == math.inf else second


    @staticmethod
    def _dfs(root):
        if root is not None:
            yield from Solution._dfs(root.left)
            yield root.val
            yield from Solution._dfs(root.right)
