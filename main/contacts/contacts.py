#!/usr/bin/env python3

from collections import defaultdict
from itertools import chain

class Trie(object):
    def __init__(self):
        self._children = defaultdict(Trie)
        self._size = 0

    def add(self, name):
        node = self
        for ch in name:
            node._size += 1
            node = node._children[ch]
        node._size += 1

    def find(self, partial):
        node = self
        for ch in partial:
            if node._size == 0:
                return 0
            node = node._children[ch]
        return node._size

trie = Trie()

for _ in range(int(input())):
    act, arg = input().split()
    if act == 'add':
        trie.add(arg)
    elif act == 'find':
        print(trie.find(arg))
    else:
        raise ValueError('don\'t know how to "%s"' % act)
