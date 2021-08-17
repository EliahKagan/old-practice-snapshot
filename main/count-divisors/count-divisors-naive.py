#!/usr/bin/env python3

left, right, k = map(int, input().split())
print(sum(1 for i in range(left, right + 1) if i % k == 0))
