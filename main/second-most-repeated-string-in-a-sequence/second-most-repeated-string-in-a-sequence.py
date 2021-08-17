#!/usr/bin/env python3

from collections import Counter

for _ in range(int(input())):
    input() # don't need n
    print(Counter(input().split()).most_common(2)[-1][0])
