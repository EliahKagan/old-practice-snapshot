#!/usr/bin/env python3

left, right, k = map(int, input().split())
count = right // k - left // k
print(count + 1 if left % k == 0 else count)
