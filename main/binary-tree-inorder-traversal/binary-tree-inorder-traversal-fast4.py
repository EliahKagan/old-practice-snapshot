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
        def dfs(node):
            stack = []
            while node or stack:
                while node: # traverse left
                    stack.append(node)
                    node = node.left

                node = stack.pop()
                yield node.val

                node = node.right

        return list(dfs(root))
