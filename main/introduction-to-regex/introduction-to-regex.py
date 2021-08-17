#!/usr/bin/env python3

import re;

PATTERN = re.compile(r'[+-]?\d*\.\d+')

for _ in range(int(input())):
    print(bool(PATTERN.fullmatch(input().strip())))
