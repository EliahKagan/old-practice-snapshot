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
        if root is None:
            return True

        stack = [(root.left, root.right)]
        while stack:
            left, right = stack.pop()
            if left is None or right is None:
                if left is not None or right is not None:
                    return False
            else:
                if left.val != right.val:
                    return False
                stack.append((left.right, right.left))
                stack.append((left.left, right.right))

        return True
