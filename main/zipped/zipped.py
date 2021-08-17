#!/usr/bin/env python3

width, height = map(int, input().split())
rows = (map(float, input().split()) for _ in range(height))

for col in zip(*rows):
    print(sum(col) / height)
