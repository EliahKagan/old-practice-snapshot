#!/usr/bin/env python3

import contextlib

def rotations(text):
    for i in range(len(text)):
        yield text[i:] + text[:i]

def find_by_rotation(lookup, key):
    for rot in rotations(key):
        with contextlib.suppress(KeyError):
            return lookup[rot]

    raise KeyError('no rotation present as key')

def partition_by_rotations(cities):
    results = []
    lookup = {}

    for city in cities:
        key = city.casefold()

        try:
            row = find_by_rotation(lookup, key)
        except KeyError:
            row = []
            results.append(row)
            lookup[key] = row

        row.append(city)

    return results

a = ['Tokyo', 'London', 'Rome', 'Donlon', 'Kyoto', 'Paris']
print(partition_by_rotations(a))
