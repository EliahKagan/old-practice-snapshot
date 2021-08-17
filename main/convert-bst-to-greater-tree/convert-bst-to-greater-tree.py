# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def convertBST(self, root):
        """
        :type root: TreeNode
        :rtype: TreeNode
        """
        def dfs(node):
            if node is not None:
                yield from dfs(node.right)
                yield node
                yield from dfs(node.left)
        
        acc = 0
        for node in dfs(root):
            acc += node.val
            node.val = acc
        
        dfs(root)
        return root
