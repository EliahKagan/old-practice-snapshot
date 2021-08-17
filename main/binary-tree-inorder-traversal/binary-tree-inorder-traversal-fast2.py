# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def inorderTraversal(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        stack = []
        while root is not None:
            stack.append(root)
            root = root.left

        ret = []
        while stack:
            root = stack.pop()
            ret.append(root.val)
            root = root.right

            while root is not None:
                stack.append(root)
                root = root.left

        return ret
