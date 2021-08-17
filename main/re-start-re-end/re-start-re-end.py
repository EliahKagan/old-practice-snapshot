#!/usr/bin/env python3

import re

s = input().strip()
r = re.compile(input().strip())
i = 0
no_matches = True

while True:
    m = r.search(s, i)

    if m is None:
        break

    print('({}, {})'.format(m.start(), m.end() - 1))
    no_matches = False

    i = m.start() + 1

if no_matches:
    print('(-1, -1)')
