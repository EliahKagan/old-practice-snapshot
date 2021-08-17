#!/usr/bin/env python3

import re

MOBILE = re.compile(r'[789]\d{9}')

for _ in range(int(input())):
    print('YES' if MOBILE.fullmatch(input().strip()) else 'NO')
