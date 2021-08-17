# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def reverseKGroup(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """
        sentinel = ListNode(None)
        sentinel.next = head
        left = sentinel

        while True:
            new_last = self._splice_out(left, k)
            if new_last is None:
                break

            new_first = self._reverse(new_last)
            new_last.next = left.next
            left.next = new_first

            left = new_last

        return sentinel.next

    def _splice_out(self, sentinel, k):
        '''Removes and returns the list of k nodes after sentinel.'''
        assert k > 0

        last = sentinel
        for _ in range(k):
            last = last.next
            if last is None:
                return None

        first = sentinel.next
        sentinel.next = last.next
        last.next = None
        return first

    def _reverse(self, head):
        '''Reverses the lists that starts at head.'''
        acc = None
        while head is not None:
            tail = head.next
            head.next = acc
            acc = head
            head = tail
        return acc
