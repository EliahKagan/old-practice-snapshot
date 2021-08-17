#!/usr/bin/env python3

input() # don't need n
heights = sorted(map(int, input().split()))

floor = 0
for index, height in enumerate(heights):
    if floor < height:
        print(len(heights) - index)
        floor = height
