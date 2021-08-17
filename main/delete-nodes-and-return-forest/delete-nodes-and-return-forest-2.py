# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    @staticmethod
    def delNodes(root: TreeNode, to_delete: List[int]) -> List[TreeNode]:
        """
        Removes nodes with the specified values.
        Returns a list roots of the resulting forest.
        """
        return forest_without(root, frozenset(to_delete))


def forest_without(root, vals):
    """Removes nodes with specified values. Lists the resulting roots."""
    roots = []

    def dfs(node):
        if not node:
            return None

        node.left = dfs(node.left)
        node.right = dfs(node.right)

        if node.val in vals:
            if node.left:
                roots.append(node.left)
            if node.right:
                roots.append(node.right)
            return None

        return node

    root = dfs(root)
    if root:
        roots.append(root)
    return roots
