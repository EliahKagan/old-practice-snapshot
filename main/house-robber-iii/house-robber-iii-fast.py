# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def rob(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        memo = {(None, False): 0, (None, True): 0}

        def dfs(node, must_skip):
            try:
                return memo[node, must_skip]
            except KeyError:
                if must_skip:
                    ret = dfs(node.left, False) + dfs(node.right, False)
                else:
                    ret = max(dfs(node, True),
                              node.val + dfs(node.left, True) + dfs(node.right, True))

                memo[node, must_skip] = ret
                return ret

        return dfs(root, False)
