#!/usr/bin/env python3


def read_text():
    """Reads a line of text, stripping whitespace."""
    return input().strip()


def distance(s, t):
    """Wagner-Fischer algorithm"""
    if len(s) < len(t):
        s, t = t, s

    pre = [None] * (len(t) + 1)
    cur = list(range(len(pre)))

    for i, sc in enumerate(s, 1):
        pre, cur = cur, pre
        cur[0] = i

        for j, tc in enumerate(t, 1):
            if sc == tc:
                cur[j] = pre[j - 1]
            else:
                cur[j] = 1 + min(cur[j - 1], pre[j], pre[j - 1])

    return cur[-1]


for _ in range(int(input())):
    print(distance(read_text(), read_text()))
