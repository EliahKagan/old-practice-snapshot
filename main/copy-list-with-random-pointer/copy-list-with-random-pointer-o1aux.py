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
        """
        Clones a singly linked list with random pointers (SLLR). This
        implementation uses O(1) space auxiliary to the input and output SLLRs,
        but it is not thread-safe. While operating, it temporarily changes the
        original SLLR.
        """
        # Make new nodes and interleave them with the originals in two separate
        # steps, so the original is *less likely* to be modified if an
        # allocation fails. (That could still happen; this is Python.)
        interleave(head, clone_without_randoms(head))

        # Populate the new nodes' random pointers.
        cur = head
        while cur:
            assert cur.next, 'odd number of nodes populating random pointers'
            assert not cur.next.random, 'random pointer unexpectedly populated'

            if cur.random:
                assert cur.random.next, 'random node lacks interleaved partner'
                cur.next.random = cur.random.next

            cur = cur.next.next

        # Separate the SLLRs and return the head of the new SLLR.
        return deinterleave(head)


def clone_without_randoms(head):
    """Clones an SLLR without populating the new SLLR's random pointers."""
    out_dummy = Node(None, None, None)
    out_cur = out_dummy

    while head:
        out_cur.next = Node(head.val, None, None)
        out_cur = out_cur.next
        head = head.next

    return out_dummy.next


def interleave(first, second):
    """Interleaves the nodes of two same-length SLLRs."""
    while first:
        assert second, 'the first is longer than the second'

        next_second = second.next
        second.next = first.next
        first.next = second
        second = next_second

        first = first.next.next

    assert not second, 'the first is shorter than the second'


def deinterleave(head):
    """
    Restores an interleaved SLLR to two separate SLLRs.
    Returns the second head.
    """
    out_dummy = Node(None, None, None)
    out_cur = out_dummy

    while head:
        assert head.next, 'odd number of nodes in interleaved SLLR'

        out_cur.next = head.next
        head.next = head.next.next
        head = head.next

        out_cur = out_cur.next

    out_cur.next = None
    return out_dummy.next
