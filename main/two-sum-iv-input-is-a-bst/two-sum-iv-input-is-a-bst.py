class Solution:
    def findTarget(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: bool
        """
        compl = set()

        def dfs(node):
            if node is None:
                return False
            if node.val in compl:
                return True
            compl.add(k - node.val)
            return dfs(node.left) or dfs(node.right)

        return dfs(root)
