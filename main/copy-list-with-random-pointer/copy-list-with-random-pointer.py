"""
# Definition for a Node.
class Node:
    def __init__(self, val, next, random):
        self.val = val
        self.next = next
        self.random = random
"""
class Solution:
    def copyRandomList(self, head: 'Node') -> 'Node':
        """Clones a singly linked list with random pointers."""
        nodes = {None: None}  # (old node -> new node) mappings

        # Clone the list except random pointers. Populate node mappings.
        out_dummy = Node(None, None, None)
        out_cur = out_dummy
        in_cur = head
        while in_cur:
            out_cur.next = Node(in_cur.val, None, None)
            out_cur = out_cur.next
            nodes[in_cur] = out_cur
            in_cur = in_cur.next

        # Populate corresponding random pointers from node mappings.
        in_cur = head
        out_cur = out_dummy.next
        while out_cur:
            out_cur.random = nodes[in_cur.random]
            out_cur = out_cur.next
            in_cur = in_cur.next

        return out_dummy.next
