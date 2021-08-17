#!/usr/bin/env python3

for _ in range(int(input())):
    print(''.join(sorted(input().strip(), reverse=True)))
