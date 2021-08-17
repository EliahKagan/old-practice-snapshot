#!/usr/bin/env python3

from sys import stdin

class Node(object):
    '''A sentinel node or data node of a circular doubly-linked list (CDLL).'''
    def __init__(self, sentinel=None, key=None):
        '''Constructs a node and places it in a new or existing CDLL.'''
        if sentinel is None: # This is a new CDLL's sentinel node.
            assert key is None
            self.key = None
            self.left = self.right = self
        else: # This is a new data node at the front of an existing CDLL.
            assert key is not None
            self.key = key
            sentinel._splice_detached_right(self)

    def __iter__(self):
        '''Yields other nodes' keys, moving right (invoke it on a sentinel).'''
        cur = self.right
        while cur is not self:
            yield cur.key
            cur = cur.right

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
    '''A least-recently-used cache, storing just keys (no associated data).'''
    def __init__(self, capacity):
        '''Initializes the cache.'''
        if capacity <= 0:
            raise ValueError('capacity must be positive')

        self._capacity = capacity
        self._length = 0
        self._queue = Node()
        self._table = {}

    def __iter__(self):
        '''Yields all keys, from highest to lowest priority.'''
        return iter(self._queue)

    def bump(self, key):
        '''Moves key to front, inserting it if not already present. Returns the
        number of "faults," which 0 if the key was present or 1 otherwise.'''
        try:
            self._queue.splice_right(self._table[key])
            return 0
        except KeyError:
            if self._length == self._capacity: # reuse the lowest-priority node
                node = self._queue.left
                del self._table[node.key]       # remove the old table key
                self._table[key] = node         # insert the new table key
                self._queue.splice_right(node)  # bump the queue node
                node.key = key                  # update the queue node's key
            else: # add a new node
                assert self._length < self._capacity
                self._length += 1                         # update the length
                self._table[key] = Node(self._queue, key) # update containers
            return 1

    def bump_multiple(self, keys):
        '''Bumps the specified keys in order, and return the "fault" count.'''
        return sum(map(self.bump, keys))

def read_record(length, slurp=False):
    '''Reads a record, raising ValueError if its length is not as specified.'''
    tokens = (stdin.read() if slurp else stdin.readline()).split()
    if len(tokens) != length:
        raise ValueError('wrong record length')
    return map(int, tokens)

n, s = read_record(2)
cache = LRUCache(s)
print(cache.bump_multiple(read_record(n, True)))
print(*cache)
