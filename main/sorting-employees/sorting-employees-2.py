#!/usr/bin/env python3

from itertools import starmap
import re

EMPLOYEE_REGEX = re.compile(r'(?P<name>\w+)\W+(?P<salary>\d+)')

def read_employees():
    input() # don't need n

    for match in EMPLOYEE_REGEX.finditer(input()):
        yield int(match.group('salary')), match.group('name')

def print_employees(employees):
    print(*starmap(lambda salary, name: '{} {}'.format(name, salary),
                   employees))

for _ in range(int(input())):
    print_employees(sorted(read_employees()))
