#!/usr/bin/env python3

def rotations(text):
    for i in range(len(text)):
        yield text[i:] + text[:i]

def partition_by_rotations(cities):
    results = []
    lookup = {}

    for city in cities:
        key = city.casefold()

        try:
            row = lookup[key]
        except KeyError:
            row = []
            results.append(row)
            for rot in rotations(key):
                lookup[rot] = row

        row.append(city)

    return results

a = ['Tokyo', 'London', 'Rome', 'Donlon', 'Kyoto', 'Paris']
print(partition_by_rotations(a))
