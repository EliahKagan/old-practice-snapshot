#!/usr/bin/env python3

class Trie(object):
    def __init__(self):
        self._elems = {}
        self._count = 0

    def add(self, word):
        cur = self

        for ch in word:
            cur._count += 1
            try:
                cur = cur._elems[ch]
            except KeyError:
                nxt = Trie()
                cur._elems[ch] = nxt
                cur = nxt

        cur._count += 1

    def query(self, prefix):
        node = self

        try:
            for ch in prefix:
                node = node._elems[ch]
        except KeyError:
            return 0

        assert node._count
        return node._count

def read_range():
    return range(int(input()))

def read_strs():
    for _ in read_range():
        yield input().strip()

for _ in read_range():
    trie = Trie()
    for word in read_strs():
        trie.add(word)
    for prefix in read_strs():
        print(trie.query(prefix))
