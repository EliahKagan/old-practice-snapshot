#!/usr/bin/env python3

from collections import defaultdict

class Trie(object):
    def __init__(self):
        self._children = defaultdict(Trie)
        self._visited = False
        self._terminal = False

    def add_and_check(self, word):
        node = self

        for ch in word:
            if node._terminal:
                return False
            node._visited = True
            node = node._children[ch]

        if node._visited:
            return False

        node._visited = node._terminal = True
        return True

trie = Trie()

for _ in range(int(input())):
    word = input().strip()
    if not trie.add_and_check(word):
        print('BAD SET')
        print(word)
        exit()

print('GOOD SET')
