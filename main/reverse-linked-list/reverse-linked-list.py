# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def reverseList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        acc = None
        while head is not None:
            tail = head.next
            head.next = acc
            acc = head
            head = tail
        return acc
