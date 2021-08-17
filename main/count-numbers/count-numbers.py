#!/usr/bin/env python3

import re

PATTERN = re.compile(r'\d+')

def count_numbers(s):
    return len(PATTERN.findall(s))

for _ in range(int(input())):
    input() # don't need n
    print(count_numbers(input()))
