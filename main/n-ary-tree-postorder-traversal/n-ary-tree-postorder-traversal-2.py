"""
# Definition for a Node.
class Node(object):
    def __init__(self, val, children):
        self.val = val
        self.children = children
"""
class Solution(object):
    def postorder(self, root):
        """
        :type root: Node
        :rtype: List[int]
        """
        acc = []

        def dfs(node):
            for child in node.children:
                dfs(child)
            acc.append(node.val)

        if root is not None:
            dfs(root)

        return acc
