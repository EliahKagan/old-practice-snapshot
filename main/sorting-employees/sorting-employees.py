#!/usr/bin/env python3

from itertools import chain
import re

EMPLOYEE_REGEX = re.compile(r'(?P<name>\w+)\W+(?P<salary>\d+)')

def read_employees():
    input() # don't need n

    for match in EMPLOYEE_REGEX.finditer(input()):
        yield match.group('name'), int(match.group('salary'))

def get_name(employee):
    name, _ = employee
    return name

def get_salary(employee):
    _, salary = employee
    return salary

def print_nested(nested):
    print(' '.join(map(str, chain.from_iterable(nested))))

for _ in range(int(input())):
    employees = list(read_employees())
    employees.sort(key=get_name)
    employees.sort(key=get_salary)
    print_nested(employees)
