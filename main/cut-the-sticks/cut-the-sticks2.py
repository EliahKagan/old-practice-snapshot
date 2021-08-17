#!/usr/bin/env python3

input() # don't need n
heights = sorted(map(int, input().split()))
countdown = range(len(heights), 0, -1)

floor = 0
for height, remaining in zip(heights, countdown):
    if floor < height:
        print(remaining)
        floor = height
