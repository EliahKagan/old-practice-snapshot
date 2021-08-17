#!/usr/bin/env python3

for _ in range(int(input())):
    input() # don't need n
    enemies = list(map(int, input().split()))
    weakest = min(enemies)
    strongest = max(enemies)
    print(sum(1 for e in enemies if e != weakest and e != strongest))
