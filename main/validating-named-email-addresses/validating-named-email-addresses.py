#!/usr/bin/env python3

import re
from email.utils import parseaddr

EMAIL = re.compile(r'[A-Za-z][A-Za-z0-9_.-]*@[A-Za-z]+\.[A-Za-z]{1,3}')

for _ in range(int(input())):
    line = input().strip()
    _, addr = parseaddr(line)
    if EMAIL.fullmatch(addr):
        print(line)
