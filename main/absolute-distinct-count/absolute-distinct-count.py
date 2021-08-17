#!/usr/bin/env python3

for _ in range(int(input())):
    input() # don't need n
    print(len(set(abs(int(tok)) for tok in input().split())))
