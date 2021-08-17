#!/usr/bin/env python3

import contextlib
import types

def objectify(mapping, target=types.SimpleNamespace()):
    for key, value in mapping.items():
        with contextlib.suppress(AttributeError):
            value = objectify(value)
        target.__setattr__(key, value)
    return target

root = objectify({'$id': '1', 'child': None, 'next': {'$id': '2', 'child': None, 'next': {'$id': '3', 'child': {'$id': '7', 'child': None, 'next': {'$id': '8', 'child': {'$id': '11', 'child': None, 'next': {'$id': '12', 'child': None, 'next': None, 'prev': {'$ref': '11'}, 'val': 12}, 'prev': None, 'val': 11}, 'next': {'$id': '9', 'child': None, 'next': {'$id': '10', 'child': None, 'next': None, 'prev': {'$ref': '9'}, 'val': 10}, 'prev': {'$ref': '8'}, 'val': 9}, 'prev': {'$ref': '7'}, 'val': 8}, 'prev': None, 'val': 7}, 'next': {'$id': '4', 'child': None, 'next': {'$id': '5', 'child': None, 'next': {'$id': '6', 'child': None, 'next': None, 'prev': {'$ref': '5'}, 'val': 6}, 'prev': {'$ref': '4'}, 'val': 5}, 'prev': {'$ref': '3'}, 'val': 4}, 'prev': {'$ref': '2'}, 'val': 3}, 'prev': {'$ref': '1'}, 'val': 2}, 'prev': None, 'val': 1})
print(root)
