#!/usr/bin/env python3

import re;

PATTERN = re.compile(r'\s*(?:0|91)?[789]\d{9}\s*')

for t in range(int(input())):
    print('Valid' if PATTERN.fullmatch(input()) else 'Invalid')
