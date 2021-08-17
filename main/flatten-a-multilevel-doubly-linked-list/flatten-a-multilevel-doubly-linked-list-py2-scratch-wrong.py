#!/usrb/bin/env python2

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
    if root is None:
        return
    yield root
    for node in preorder_nodes(root.child):
        yield node
    for node in preorder_nodes(root.next):
        yield node

def debug(head):
    while head is not None:
        print head.val,
        head = head.next
    print
        
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
        
        sentinel.next.prev = None
        debug(sentinel.next)
        return sentinel.next
