#!/usr/bin/env python3

from collections import defaultdict
from itertools import chain

def get_initials(word):
    return ''.join(c for c in word if c.isupper())

def group_by_initials(line):
    groups = defaultdict(list)

    for word in line.split():
        groups[get_initials(word)].append(word)

    return groups

def get_matching_initials(groups, pattern):
    stripped_pattern = pattern.strip()

    return (initials for initials in groups.keys()
                     if initials.startswith(stripped_pattern))

def filter_by_match(groups, pattern):
    matching_initials = sorted(get_matching_initials(groups, pattern))
    return (groups[initials] for initials in matching_initials)

def compute_matches(line, pattern):
    groups = group_by_initials(line)
    matching_groups = filter_by_match(groups, pattern)
    return chain.from_iterable(matching_groups)

for _ in range(int(input())):
    input() # don't need n
    line = input()
    pattern = input()
    matches = compute_matches(line, pattern)
    result = ' '.join(matches)
    print('No match found' if len(result) == 0 else result)
