#!/usr/bin/env python3

import re

PATTERN = re.compile('\d+')

for _ in range(int(input())):
    print(max(map(int, PATTERN.findall(input()))))
