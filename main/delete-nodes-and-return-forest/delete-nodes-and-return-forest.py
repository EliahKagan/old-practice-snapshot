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
        return list(forest_without(root, frozenset(to_delete)))


def forest_without(root, vals):
    """Removes nodes with specified values. Yields the remaining roots."""
    def dfs_root(node):
        if not node:
            return

        if node.val in vals:
            yield from dfs_root(node.left)
            yield from dfs_root(node.right)
        else:
            yield node
            yield from dfs_left(node)
            yield from dfs_right(node)

    def dfs_left(parent):
        child = parent.left
        if not child:
            return

        if child.val in vals:
            parent.left = None
            yield from dfs_root(child)
        else:
            yield from dfs_left(child)
            yield from dfs_right(child)

    def dfs_right(parent):
        child = parent.right
        if not child:
            return

        if child.val in vals:
            parent.right = None
            yield from dfs_root(child)
        else:
            yield from dfs_left(child)
            yield from dfs_right(child)

    return dfs_root(root)
