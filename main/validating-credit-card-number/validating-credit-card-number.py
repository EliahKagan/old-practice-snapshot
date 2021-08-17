#!/usr/bin/env python3

import re

CCNUM = re.compile(r'(?!.*(\d)(?:\D?\1){3})[456]\d{3}(-?)(?:\d{4}\2){2}\d{4}')

for _ in range(int(input())):
    print('Valid' if CCNUM.fullmatch(input().strip()) else 'Invalid')
