#!/usr/bin/env python3

from collections import Counter

for _ in range(int(input())):
    counts = Counter(input().strip())
    max_count = counts.most_common(1)[0][1]
    print(max(digit for digit in counts if counts[digit] == max_count))
