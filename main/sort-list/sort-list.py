# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

import contextlib

class Solution:
    @staticmethod
    def sortList(head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        length = 1
        while True:
            newHead = Solution._mergePass(head, length)
            if newHead is None:
                break

            head = newHead
            length *= 2

        return head

    @staticmethod
    def _mergePass(head, length):
        sentinel = ListNode(...)
        sentinel.next = head
        beforeFirst = sentinel

        while True:
            beforeSecond = Solution._advance(beforeFirst, length)
            second = Solution._advance(beforeSecond, 1)
            if second is None:
                break # no second half to merge with
            beforeSecond.next = None

            beforeThird = Solution._advance(second, length - 1)
            third = Solution._advance(beforeThird, 1)
            if third is not None:
                beforeThird.next = None

            beforeFirst.next, last = Solution._merge(beforeFirst.next, second)
            last.next = third
            beforeFirst = last

        return None if beforeFirst is sentinel else sentinel.next

    @staticmethod
    def _advance(node, distance):
        with contextlib.suppress(AttributeError):
            for _ in range(distance):
                node = node.next
        return node

    @staticmethod
    def _merge(first, second):
        sentinel = ListNode(...)
        cur = sentinel

        while first is not None and second is not None:
            if second.val < first.val:
                cur.next = second
                second = second.next
            else:
                cur.next = first
                first = first.next
            cur = cur.next

        cur.next = (first if second is None else second)
        while cur.next is not None:
            cur = cur.next

        return sentinel.next, cur
