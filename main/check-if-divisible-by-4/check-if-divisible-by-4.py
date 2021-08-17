#!/usr/bin/env python3

for t in range(int(input())):
    print('1' if int(input().strip()[-2:]) % 4 == 0 else '0')
