#!/usr/bin/env python3

import re

AND = re.compile(r'(?<= )&&(?= )')
OR = re.compile(r'(?<= )\|\|(?= )')

for _ in range(int(input())):
    print(OR.sub('or', AND.sub('and', input())))
