#!/usr/bin/env python3

def read_val():
    return int(input())

def read_record():
    return map(int, input().split())

for _ in range(read_val()):
    n = read_val()
    print('YES' if n * (n + 1) // 2 == sum(read_record()) else 'NO')
