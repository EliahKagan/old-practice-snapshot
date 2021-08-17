#!/usr/bin/env python3

import re

PATTERN = re.compile('\d+')

for _ in range(int(input())):
    print(sum(int(digits) for digits in PATTERN.findall(input())))
