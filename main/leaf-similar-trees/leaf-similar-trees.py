# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

def leaves(root):
    if root is None:
        return

    if root.left is None and root.right is None:
        yield root.val
    else:
        yield from leaves(root.left)
        yield from leaves(root.right)

class Solution:
    def leafSimilar(self, root1, root2):
        """
        :type root1: TreeNode
        :type root2: TreeNode
        :rtype: bool
        """
        return all(x == y for x, y in itertools.zip_longest(leaves(root1),
                                                            leaves(root2)))
