class Node(object):
    '''A sentinel node or data node of a circular doubly-linked list (CDLL).'''
    def __init__(self, sentinel=None, key=None, value=None):
        '''Constructs a node and places it in a new or existing CDLL.'''
        if sentinel is None: # This is a new CDLL's sentinel node.
            assert key is None and value is None
            self.key = self.value = None
            self.left = self.right = self
        else: # This is a new data node at the front of an existing CDLL.
            assert key is not None and value is not None
            self.key = key
            self.value = value
            sentinel._splice_detached_right(self)

    def splice_right(self, other):
        '''Inserts other right of self, after relinking other's neighbors.'''
        other.left.right = other.right
        other.right.left = other.left
        self._splice_detached_right(other)

    def _splice_detached_right(self, other):
        '''Inserts other right of self. Assumes other is not already linked.'''
        other.left = self
        other.right = self.right
        self.right.left = other
        self.right = other

class LRUCache(object):
    '''A least-recently-used cache, storing keys and associated values.'''
    def __init__(self, capacity, default_value=-1):
        '''Initializes the cache.'''
        if capacity <= 0:
            raise ValueError('capacity must be positive')

        self._capacity = capacity
        self._length = 0
        self._default_value = default_value
        self._queue = Node()
        self._table = {}

    def get(self, key):
        '''Bumps the node for the specified key, returning the stored value.'''
        try:
            node = self._table[key]
            self._queue.splice_right(node)
            return node.value
        except KeyError:
            return self._default_value

    def put(self, key, value):
        '''Inserts or updates (and bumps) the key with the specified value.'''
        try:
            node = self._table[key]
            node.value = value
            self._queue.splice_right(node)
        except KeyError:
            if self._length == self._capacity: # reuse the lowest-priority node
                node = self._queue.left
                del self._table[node.key]
                self._table[key] = node
                self._queue.splice_right(node)
                node.key = key
                node.value = value
            else:                              # add a new node
                assert self._length < self._capacity
                self._length += 1
                self._table[key] = Node(self._queue, key, value)


# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)
