#!/usr/bin/env python3

from collections import OrderedDict

word_counts = OrderedDict()

for _ in range(int(input())):
    word = input().strip()
    try:
        word_counts[word] += 1
    except KeyError:
        word_counts[word] = 1

print(len(word_counts))
print(*word_counts.values())
