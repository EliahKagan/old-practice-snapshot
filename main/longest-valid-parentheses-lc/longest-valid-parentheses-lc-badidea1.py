class Link:
    __slots__ = ('key', 'left', 'right')

    def __init__(self, key, left, right):
        self.key = key
        self.left = left
        self.right = right

OPENER = -1
CLOSER = -2

def tokenize(s):
    last = len(s) - 1
    i = 0
    while i < last:
        if s[i] == ')':
            i += 1
            yield CLOSER
        elif s[i + 1] == ')':
            i += 2
            yield 2
        else:
            i += 1
            yield OPENER

    if i == last:
        yield CLOSER if s[i] == ')' else OPENER

def make_chain(tokens):
    sentinel = Link(None, None, None)
    cur = sentinel

    for tok in tokens:
        cur.right = Link(tok, cur, None)
        cur = cur.right

    return sentinel.right

def reduce_chain(head):
    again = True
    while again:
        again = False
        cur = head

        while cur.next is not None:


class Solution:
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
