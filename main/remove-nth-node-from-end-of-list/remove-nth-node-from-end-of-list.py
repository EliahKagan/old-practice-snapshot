# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def removeNthFromEnd(self, head, n):
        """
        :type head: ListNode
        :type n: int
        :rtype: ListNode
        """
        right = head
        for _ in range(n):
            right = right.next

        sentinel = ListNode(None)
        sentinel.next = head

        left = sentinel
        while right is not None:
            right = right.next
            left = left.next

        left.next = left.next.next
        return sentinel.next
