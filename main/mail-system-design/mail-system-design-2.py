#!/usr/bin/env python3

from itertools import chain

UNREAD_TO_READ = 1
READ_TO_TRASH = 2
UNREAD_TO_TRASH = 3
TRASH_TO_READ = 4

class Node(object):
    def __init__(self, left, right):
        self.left = left
        self.right = right

def read_record(length):
    tokens = input().split()
    if len(tokens) != length:
        raise ValueError('wrong record length')
    return map(int, tokens)

def make_nodes(n):
    yield Node(n, 1)

    for i in range(1, n):
        yield Node(i - 1, i + 1)

    yield Node(n - 1, 0)

def make_sentinel(sentinel):
    return Node(sentinel, sentinel)

def splice_left(nodes, dest, src):
    nodes[nodes[src].left].right = nodes[src].right
    nodes[nodes[src].right].left = nodes[src].left

    nodes[src].left = nodes[dest].left
    nodes[src].right = dest

    nodes[nodes[dest].left].right = src
    nodes[dest].left = src

def display(nodes, sentinel):
    i = nodes[sentinel].right
    if i == sentinel:
        print('EMPTY')
        return

    def gen():
        nonlocal i
        while i != sentinel:
            yield i
            i = nodes[i].right

    print(*gen())

for _ in range(int(input())):
    # Read list length and number of queries.
    n, q = read_record(2)

    # Define the special nodes' indices and create the list.
    unread = 0
    read = n + 1
    trash = read + 1

    # Initialize all nodes by setting their left and right connections.
    nodes = [*make_nodes(n), make_sentinel(read), make_sentinel(trash)]
    assert len(nodes) == trash + 1

    # Move nodes between lists as specified in the queries.
    script = read_record(q * 2)
    for _ in range(q):
        op = next(script)
        arg = next(script)
        if not 0 < arg <= n:
            raise ValueError('message ID is out of range')

        if op == UNREAD_TO_READ or op == TRASH_TO_READ:
            splice_left(nodes, read, arg)
        elif op == READ_TO_TRASH or op == UNREAD_TO_TRASH:
            splice_left(nodes, trash, arg)
        else:
            raise ValueError('invalid opcode specified')

    #  Print each chain.
    for sentinel in (unread, read, trash):
        display(nodes, sentinel)
