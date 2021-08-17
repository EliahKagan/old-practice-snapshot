"""
# Definition for a Node.
class Node(object):
    def __init__(self, val, prev, next, child):
        self.val = val
        self.prev = prev
        self.next = next
        self.child = child
"""

def preorder_nodes(root):
    stack = [root]
    while stack:
        root = stack.pop()
        if root is None:
            continue
        stack.append(root.next)
        stack.append(root.child)
        yield root

class Solution(object):
    @staticmethod
    def flatten(head):
        """
        :type head: Node
        :rtype: Node
        """
        sentinel = Node(None, None, None, None)
        pre = sentinel

        for cur in preorder_nodes(head):
            pre.next = cur
            cur.prev = pre
            cur.child = None
            pre = cur

        pre.next = None

        if sentinel.next is not None:
            sentinel.next.prev = None
        return sentinel.next