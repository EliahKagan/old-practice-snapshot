#!/usr/bin/env python3

from collections import defaultdict
from itertools import chain

for _ in range(int(input())):
    input()  # don't need n
    phrases = input().split()
    prefix = input().strip()

    matches = defaultdict(list)
    for phrase in phrases:
        initials = ''.join(filter(str.isupper, phrase))
        if initials.startswith(prefix):
            matches[initials].append(phrase)

    sorted_matches = (matches[initials] for initials in sorted(matches))
    result = ' '.join(chain.from_iterable(sorted_matches))
    print(result if result else 'No match found')
