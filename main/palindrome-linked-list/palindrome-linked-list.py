# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    @staticmethod
    def isPalindrome(head):
        """
        :type head: ListNode
        :rtype: bool
        """
        a = list(Solution._traverse(head))
        return a == a[::-1]

    def _traverse(head):
        while head is not None:
            yield head.val
            head = head.next
