class Solution:
    def reverseBetween(self, head, m, n):
        """
        :type head: ListNode
        :type m: int
        :type n: int
        :rtype: ListNode
        """
        sentinel = ListNode(None)
        sentinel.next = head

        left = sentinel
        for _ in range(1, m):
            left = left.next

        new_last = self._splice_out(left, n - m + 1)
        new_first = self._reverse(new_last)
        new_last.next = left.next
        left.next = new_first

        return sentinel.next

    def _splice_out(self, sentinel, length):
        '''Removes and returns the list of length nodes after sentinel.'''
        assert length > 0

        last = sentinel
        for _ in range(length):
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