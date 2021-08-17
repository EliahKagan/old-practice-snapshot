#!/usr/bin/env python3

for _ in range(int(input())):
    input() # don't need n
    print(*sorted(map(int, input().split()), key = lambda x: x >= 0))
