# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def insertionSortList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        dest_sentinel = ListNode(None)

        while head is not None:
            dest = dest_sentinel
            while dest.next is not None and dest.next.val < head.val:
                dest = dest.next

            next_head = head.next
            head.next = dest.next
            dest.next = head

            head = next_head

        return dest_sentinel.next
