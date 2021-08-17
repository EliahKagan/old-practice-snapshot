#!/usr/bin/env python3

import re

input() # don't need length
pw = input().strip()

count = 0
count += not re.search(r'\d', pw)
count += not re.search(r'[A-Z]', pw)
count += not re.search(r'[a-z]', pw)
count += not re.search(r'[!@#$%^&*()+-]', pw)
print(max(count, 6 - len(pw)))
