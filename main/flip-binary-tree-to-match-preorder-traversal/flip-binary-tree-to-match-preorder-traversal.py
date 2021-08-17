# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class UnmatchableVoyage(Exception):
    pass

class Solution:
    def flipMatchVoyage(self, root, voyage):
        """
        :type root: TreeNode
        :type voyage: List[int]
        :rtype: List[int]
        """
        flips = []

        def dfs(node, i):
            if node is None:
                return i

            if node.val != voyage[i]:
                raise UnmatchableVoyage()

            if node.left is None and node.right is None:
                return i + 1

            val = voyage[i + 1]

            if (node.left is not None and node.right is not None
                    and node.left.val != val and node.right.val == val):
                node.left, node.right = node.right, node.left
                flips.append(node.val)

            return dfs(node.right, dfs(node.left, i + 1))

        try:
            if dfs(root, 0) != len(voyage):
                raise UnmatchableVoyage()
        except (UnmatchableVoyage, IndexError):
            return [-1]

        return flips
