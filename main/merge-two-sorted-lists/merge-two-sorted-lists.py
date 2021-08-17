# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def mergeTwoLists(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        left = right = ListNode(None)

        while l1 is not None and l2 is not None:
            if l1.val > l2.val:
                l1, l2 = l2, l1
            right.next = l1
            right = right.next
            l1 = l1.next

        if l1 is None:
            l1 = l2
        right.next = l1

        return left.next
