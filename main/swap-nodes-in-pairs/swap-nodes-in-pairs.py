# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def swapPairs(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        sentinel = ListNode(None)
        sentinel.next = head

        x = sentinel
        while x.next is not None and x.next.next is not None:
            # x -> y -> z -> w, need to swap y with z
            y = x.next
            z = y.next

            y.next = z.next
            z.next = y
            x.next = z

            x = y

        return sentinel.next
