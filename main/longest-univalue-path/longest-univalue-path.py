# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def longestUnivaluePath(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        best = 0

        def dfs(node):
            nonlocal best

            if node is None:
                return 0

            leftLen = dfs(node.left)
            rightLen = dfs(node.right)

            withLeft = (0 if node.left is None or node.left.val != node.val
                          else leftLen + 1)
            withRight = (0 if node.right is None or node.right.val != node.val
                           else rightLen + 1)

            best = max(best, withLeft + withRight)
            return max(withLeft, withRight)

        dfs(root)
        return best
