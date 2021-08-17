#!/usr/bin/env python3

import re

consonant = r'[qwrtypsdfghjklzxcvbnm]'
pattern = r'(?i)(?<=%s)[aeiou]{2,}(?=%s)' % (consonant, consonant)
matches = re.findall(pattern, input())
print('-1' if len(matches) == 0 else '\n'.join(matches))
