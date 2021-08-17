#!/usr/bin/env python3

from collections import defaultdict

def read_word():
    return input().strip()

word_indices = defaultdict(list)

n, m = map(int, input().split())

for i in range(1, n + 1):
    word_indices[read_word()].append(i)

for _ in range(m):
    indices = word_indices[read_word()]

    if len(indices) == 0:
        print(-1)
    else:
        print(*indices)
