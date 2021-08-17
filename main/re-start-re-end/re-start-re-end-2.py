#!/usr/bin/env python3

import re

def gets():
    return input().strip()

text = gets()
regex = re.compile(r'(?=({}))'.format(gets()))
pairs = [(match.start(1), match.end(1) - 1) for match in regex.finditer(text)]

if len(pairs) == 0:
    print((-1, -1))
else:
    print(*pairs, sep='\n')
