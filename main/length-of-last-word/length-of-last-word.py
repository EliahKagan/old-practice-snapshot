#!/usr/bin/env python3

import re

PATTERN = re.compile(r'\w*(?=\W*$)')

for _ in range(int(input())):
    print(len(PATTERN.search(input())[0]))
