#!/usr/bin/env python3

import re

PATTERN = re.compile(r'(?:[a-mo-su-z]|(?<!\\)[nt])+')

for _ in range(int(input())):
    print(len(PATTERN.findall(input())))
