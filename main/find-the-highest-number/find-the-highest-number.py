#!/usr/bin/env python3

# N is small; the constant time benefit of stopping when all numbers
# are lower is not worth the extra code complexity.

for _ in range(int(input())):
    input()
    print(max(map(int, input().split())))
