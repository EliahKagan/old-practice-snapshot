#!/usr/bin/env python3

from collections import Counter, OrderedDict

class OrderedCounter(Counter, OrderedDict):
    pass

word_counts = OrderedCounter(input().strip() for _ in range(int(input())))
print(len(word_counts))
print(*word_counts.values())
