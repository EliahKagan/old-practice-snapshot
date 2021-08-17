#!/usr/bin/env python3

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    if len(a) != n:
        raise ValueError('wrong record length')

    # table[width][start] will be the minimum value in the window of that width
    # with that start index (i.e., start indexes the window's leftmost element)
    table = [None, a, *([None] * (n + 1 - width) for width in range(2, n + 1))]
    assert len(table) == n + 1

    for i in range(0, n - 1):
        acc = a[i]
        for j in range(i + 1, n):
            table[j - i + 1][i] = acc = min(acc, a[j])

    print(*map(max, table[1:]))
