#!/usr/bin/env python3

BIAS = ord('a')
ALPHA_LEN = ord('z') - BIAS + 1
ALPHA = 'abcdefghijklmnopqrstuvwxyz'
assert all(ord(ALPHA[i]) - BIAS == i for i in range(ALPHA_LEN)), \
        'English lower-case letters are noncontiguous'

class CharMap(object):
    def __init__(self):
        self._elems = [None] * ALPHA_LEN

    def __getitem__(self, ch):
        return self._elems[ord(ch) - BIAS]

    def __setitem__(self, ch, val):
        self._elems[ord(ch) - BIAS] = val

class Trie(CharMap):
    def __init__(self, words=()):
        super().__init__()
        self._word = None

        for word in words:
            cur = self
            for ch in word:
                if cur[ch] is None:
                    cur[ch] = Trie()
                cur = cur[ch]
            cur._word = word

    @property
    def word(self):
        return self._word

class Solution:
    def findWords(self, board, words):
        """
        :type board: List[List[str]]
        :type words: List[str]
        :rtype: List[str]
        """
        istop = len(board)
        jstop = len(board[0])
        assert all(len(row) == jstop for row in board)
        matches = []

        def dfs(trie, i, j):
            if i == -1 or i == istop or j == -1 or j == jstop:
                return

            ch = board[i][j]
            if ch is None:
                return

            trie = trie[ch]
            if trie is None:
                return

            if trie.word is not None:
                matches.append(trie.word)

            board[i][j] = None
            dfs(trie, i, j - 1)
            dfs(trie, i, j + 1)
            dfs(trie, i - 1, j)
            dfs(trie, i + 1, j)
            board[i][j] = ch

        root = Trie(words)
        for i in range(istop):
            for j in range(jstop):
                dfs(root, i, j)

        return list(set(matches))
