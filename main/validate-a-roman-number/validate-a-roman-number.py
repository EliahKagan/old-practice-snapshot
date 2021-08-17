#!/usr/bin/env python3

import re

# Similar to roman.romanNumeralPattern (https://pypi.python.org/pypi/roman)
ROMAN = r'(?=.)M{0,3}(?:C[MD]|D?C{0,3})(?:X[CL]|L?X{0,3})(?:I[XV]|V?I{0,3})'

print(re.fullmatch(ROMAN, input().strip()) is not None)
