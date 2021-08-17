#!/usr/bin/env python3

class Trie(object):
    def __init__(self):
        self._children = {}
        self._word = None

    def __getitem__(self, ch):
        return self._children[ch]

    def __iter__(self):
        if self._word is not None:
            yield self._word

        for ch in sorted(self._children):
            yield from self._children[ch]

    def add(self, word):
        cur = self

        for ch in word:
            try:
                cur = cur._children[ch]
            except KeyError:
                nxt = Trie()
                cur._children[ch] = nxt
                cur = nxt

        cur._word = word

    def extend(self, words):
        for word in words:
            self.add(word)

FALLBACK = '0'  # text to print when there are no matches

for _ in range(int(input())):
    input()  # don't need n

    # Build the trie.
    trie = Trie()
    trie.extend(input().split())

    # Look up the specified word, (re)enumerating all words at each step.
    for ch in input().strip():
        try:
            trie = trie[ch]
        except TypeError:   # the trie has already been discarded
            print(FALLBACK)
        except KeyError:    # the trie does not contain this prefix
            trie = None
            print(FALLBACK)
        else:
            print(' '.join(trie))
