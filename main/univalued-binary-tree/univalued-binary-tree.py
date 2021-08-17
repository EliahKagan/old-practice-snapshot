# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def isUnivalTree(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        if root is None:
            return True # "every node in the tree has the same value"

        val = root.val

        def dfs(node):
            if node is None:
                return True
            return node.val == val and dfs(node.left) and dfs(node.right)

        return dfs(root.left) and dfs(root.right)
