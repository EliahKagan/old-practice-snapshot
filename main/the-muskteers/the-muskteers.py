#!/usr/bin/env python3
import re

r = re.compile(r'1*0+1*')

for t in range(int(input())):
    print('YES' if r.fullmatch(input().strip()) else 'NO')
