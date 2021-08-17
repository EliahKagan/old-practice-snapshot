# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def deepestLeavesSum(self, root: TreeNode) -> int:
        """Computes the sum of node values from the lowermost level."""
        return sum(node.val for node in deepest_level(root))


def deepest_level(root: TreeNode) -> List[TreeNode]:
    """Gets the nodes of the lowermost level of a binary tree."""
    if not root:
        return []

    children = [root]
    parents = []

    while children:
        parents, children = children, parents
        children.clear()

        for node in parents:
            if node.left:
                children.append(node.left)
            if node.right:
                children.append(node.right)

    return parents
