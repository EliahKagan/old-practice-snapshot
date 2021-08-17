#!/usr/bin/env python3

import re

match = re.fullmatch(r'(?!(?:.*?(.)(?=.\1)){2})[1-9]\d{5}', input().strip())
print(match is not None)
