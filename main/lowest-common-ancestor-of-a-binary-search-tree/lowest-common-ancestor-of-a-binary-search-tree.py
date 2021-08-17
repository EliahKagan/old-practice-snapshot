# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    @staticmethod
    def lowestCommonAncestor(root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode
        """
        x = p.val
        y = q.val
        while True:
            cur = root.val
            if x < root.val and y < root.val:
                root = root.left
            elif x > root.val and y > root.val:
                root = root.right
            else:
                return root
