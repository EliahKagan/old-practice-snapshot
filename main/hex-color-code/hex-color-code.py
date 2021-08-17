#!/usr/bin/env python3

import re

HEX_COLOR_CODE = re.compile(r'(?i)\S.*?(#(?:[0-9a-f]{3}){1,2})')

for _ in range(int(input())):
    for code in HEX_COLOR_CODE.findall(input()):
        print(code)
