#!/usr/bin/env python3

import re

n, m = map(int, input().split())
rows = (input().rstrip().ljust(m) for _ in range(n))
cols = (''.join(col) for col in zip(*rows))
text = ''.join(cols)
print(re.sub(r'(?<=[A-Za-z0-9])[ !@#$%&]+(?=[A-Za-z0-9])', ' ', text))
