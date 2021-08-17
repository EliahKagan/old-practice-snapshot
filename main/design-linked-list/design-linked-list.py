import contextlib

class MyLinkedList:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._sentinel = MyLinkedList._Node(None)

    def get(self, index):
        """
        Get the value of the index-th node in the linked list. If the index is invalid, return -1.
        :type index: int
        :rtype: int
        """
        try:
            return self._pre(index).nxt.key
        except IndexError:
            return self._NO_NODE

    def addAtHead(self, val):
        """
        Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
        :type val: int
        :rtype: void
        """
        self._sentinel.nxt = MyLinkedList._Node(val, self._sentinel.nxt)

    def addAtTail(self, val):
        """
        Append a node of value val to the last element of the linked list.
        :type val: int
        :rtype: void
        """
        pre = self._sentinel
        while pre.nxt is not None:
            pre = pre.nxt
        
        pre.nxt = MyLinkedList._Node(val)

    def addAtIndex(self, index, val):
        """
        Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted.
        :type index: int
        :type val: int
        :rtype: void
        """
        with contextlib.suppress(IndexError):
            pre = self._pre(index, True)
            pre.nxt = MyLinkedList._Node(val, pre.nxt)

    def deleteAtIndex(self, index):
        """
        Delete the index-th node in the linked list, if the index is valid.
        :type index: int
        :rtype: void
        """
        with contextlib.suppress(IndexError):
            pre = self._pre(index)
            pre.nxt = pre.nxt.nxt
    
    _NO_NODE = -1
    
    class _Node:
        def __init__(self, key, nxt = None):
            self.key = key
            self.nxt = nxt
    
    def _pre(self, index, allow_end = False):
        if index < 0:
            MyLinkedList._raise()
        
        pre = self._sentinel
        try:
            for _ in range(index):
                pre = pre.nxt
                
            # Raise AttributeError (then IndexError) if pre is past the end.
            # Raise IndexError directly if pre.nxt is unexpectedly at the end.
            if pre.nxt is None and not allow_end:
                MyLinkedList._raise()
        except AttributeError:
            MyLinkedList._raise()
        
        return pre
    
    @staticmethod
    def _raise():
        raise IndexError('index out of range')


# Your MyLinkedList object will be instantiated and called as such:
# obj = MyLinkedList()
# param_1 = obj.get(index)
# obj.addAtHead(val)
# obj.addAtTail(val)
# obj.addAtIndex(index,val)
# obj.deleteAtIndex(index)
