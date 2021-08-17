# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    @staticmethod
    def isSymmetric(root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        return root is None or Solution._mirrors(root.left, root.right)

    @staticmethod
    def _mirrors(left, right):
        if left is None or right is None:
            return left is None and right is None

        return (left.val == right.val
                and Solution._mirrors(left.left, right.right)
                and Solution._mirrors(left.right, right.left))
