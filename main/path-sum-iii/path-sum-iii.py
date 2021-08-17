# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def pathSum(self, root, total):
        """
        :type root: TreeNode
        :type total: int
        :rtype: int
        """
        if root is None:
            return 0

        path = []
        count = 0

        def doCount(partial):
            nonlocal count

            if partial == 0:
                count += 1
            for val in path:
                partial += val
                if partial == 0:
                    count += 1

        def dfs(node):
            nonlocal total

            total -= node.val
            doCount(total)
            path.append(node.val)

            if node.left is not None:
                dfs(node.left)
            if node.right is not None:
                dfs(node.right)

            total += path.pop()

        dfs(root)
        return count
