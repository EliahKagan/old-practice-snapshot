# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def postorderTraversal(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        ret = []
        if root is None:
            return ret

        stack = [root]
        while stack:
            root = stack.pop()
            ret.append(root.val)

            if root.left is not None:
                stack.append(root.left)
            if root.right is not None:
                stack.append(root.right)

        ret.reverse()
        return ret
