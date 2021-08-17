#!/usr/bin/env python3

for _ in range(int(input())):
    input() # don't need n

    try:
        print(input().index('1') // 2)
    except ValueError:
        print(-1)
