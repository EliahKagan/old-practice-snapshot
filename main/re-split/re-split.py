#!/usr/bin/env python3

import re

PATTERN = re.compile('[,.]+')

for tok in PATTERN.split(input().strip()):
    if len(tok) != 0:
        print(tok)
