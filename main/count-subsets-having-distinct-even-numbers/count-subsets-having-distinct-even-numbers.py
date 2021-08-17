#!/usr/bin/env python3

for _ in range(int(input())):
    input() # don't need n
    a  = map(int, input().split())
    print(2**len(set(x for x in a if x % 2 == 0)) - 1)
