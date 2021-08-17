#!/usr/bin/env python3

import re
m = re.search(r'([0-9A-Za-z])\1', input())
print(m.group(1) if m else '-1')
