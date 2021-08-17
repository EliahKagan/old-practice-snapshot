# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def deleteDuplicates(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        sentinel = ListNode(None)
        sentinel.next = head
        cur = sentinel

        while cur.next is not None and cur.next.next is not None:
            val = cur.next.val
            if cur.next.next.val == val:
                dest = cur.next.next.next
                while dest is not None and dest.val == val:
                    dest = dest.next
                cur.next = dest
            else:
                cur = cur.next

        return sentinel.next
