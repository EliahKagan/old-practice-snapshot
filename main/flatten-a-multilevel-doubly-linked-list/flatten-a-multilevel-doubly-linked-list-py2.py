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
    while root is not None:
        child_node = root.child
        next_node = root.next
        yield root
        
        for node in preorder_nodes(child_node):
            yield node
            
        root = next_node

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
