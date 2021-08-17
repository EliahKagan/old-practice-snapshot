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
        ret = []
        if root is None:
            return ret

        stack = [(iter(root.children), root.val)]

        while stack:
            it, val = stack[-1]

            try:
                child = next(it)
                stack.append((iter(child.children), child.val))
            except StopIteration:
                ret.append(val)
                del stack[-1]

        return ret
