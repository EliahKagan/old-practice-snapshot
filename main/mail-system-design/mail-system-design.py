#!/usr/bin/env python3

class Node(object):
    '''A sentinel node or data node of a circular doubly-linked list (CDLL).'''
    def __init__(self, sentinel=None, value=None):
        '''Constructs a node and place it in a new or existing CDLL.'''
        if sentinel is None: # This is a new CDLL's sentinel node.
            self.value = None
            self.left = self.right = self
        else: # This is a new data node at the "end" of an existing CDLL.
            self.value = value
            sentinel._splice_detached_left(self)

    def __bool__(self):
        '''Reports if there are other nodes, so a sentinel is truthy iff the
        CDLL it represents is "nonempty."'''
        return self.right is not self

    def __iter__(self):
        '''Yields all the other nodes' values, traversing to the right. So
        on a sentinel, you get "all" the values of the CDLL it represents.'''
        cur = self.right
        while cur is not self:
            yield cur.value
            cur = cur.right

    def __repr__(self):
        '''Gives a programmer-readable representation of the other nodes' values
        useful primarily for debugging.'''
        return '((' + ' -> '.join(map(str, self)) + '))'

    def __str__(self):
        '''Gives a user-readable representation of the other nodes' values.'''
        return ' '.join(map(str, self)) if self else 'EMPTY'

    def splice_left(self, other):
        '''Inserts the other node immediately to the left of this one. If self
        is a sentinel, this effectively puts other at the "end" of its CDLL.'''
        other.right.left = other.left
        other.left.right = other.right
        self._splice_detached_left(other)

    def _splice_detached_left(self, other):
        '''Inserts the other node immediately to the left of this one, without
        tending to any nodes it may be attached to already.'''
        other.right = self
        other.left = self.left
        self.left.right = other
        self.left = other

def build_range_cdll(start, stop):
    '''Generates the sentinel, and all data nodes, of a CDLL whose values are
    the same as range(start, stop).'''
    sentinel = Node()
    yield sentinel
    for value in range(start, stop):
        yield Node(sentinel, value)

def read_record(length):
    '''Reads a record, validates its length, and generates its from it.'''
    tokens = input().split()
    if len(tokens) != length:
        raise ValueError('wrong record length')
    return map(int, tokens)

UNREAD_TO_READ = 1
READ_TO_TRASH = 2
UNREAD_TO_TRASH = 3
TRASH_TO_READ = 4

for _ in range(int(input())):
    n, q = read_record(2)

    nodes = list(build_range_cdll(1, n + 1))
    unread = nodes[0]
    read = Node()
    trash = Node()

    script = read_record(q * 2)
    for _ in range(q):
        op = next(script)
        arg  = next(script)
        if not 0 < arg <= n:
            raise ValueError('query specifies an out-of-range message ID')

        if op == UNREAD_TO_READ or op == TRASH_TO_READ:
            read.splice_left(nodes[arg])
        elif op == READ_TO_TRASH or op == UNREAD_TO_TRASH:
            trash.splice_left(nodes[arg])
        else:
            raise ValueError('query specifies an invalid opcode')

    for sentinel in unread, read, trash:
        print(sentinel)
