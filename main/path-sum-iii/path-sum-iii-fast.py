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

        history = collections.Counter((0,)) # old subtotals
        cur = 0 # current subtotal
        count = 0 # the number of paths found that sum to the total

        def dfs(node):
            nonlocal cur, count

            cur += node.val
            count += history[cur - total] # count prevs where cur-prev==total
            history[cur] += 1

            if node.left is not None:
                dfs(node.left)
            if node.right is not None:
                dfs(node.right)

            history[cur] -= 1
            cur -= node.val

        dfs(root)
        return count
