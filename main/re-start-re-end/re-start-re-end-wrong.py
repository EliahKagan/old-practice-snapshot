#!/usr/bin/env python3

import re

s = input().strip()
r = re.compile(input().strip())
i = 0

while True:
    m = r.search(s, i)

    if m is None:
        break

    print('({}, {})'.format(m.start(), m.end() - 1))

    i = m.start() + 1
