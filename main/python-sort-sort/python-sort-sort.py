#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

n, _ = read_record() # don't need m
table = [list(read_record()) for _ in range(n)]
k = int(input())

table.sort(key=lambda row: row[k])

for row in table:
    print(*row)
