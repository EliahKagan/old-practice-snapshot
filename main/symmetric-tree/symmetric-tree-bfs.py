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

        queue = collections.deque()
        queue.append((root.left, root.right))

        while queue:
            left, right = queue.popleft() # this popleft is unrelated to "left"
            if left is None or right is None:
                if left is not None or right is not None:
                    return False
            elif left.val != right.val:
                return False
            else:
                queue.append((left.left, right.right))
                queue.append((left.right, right.left))

        return True
