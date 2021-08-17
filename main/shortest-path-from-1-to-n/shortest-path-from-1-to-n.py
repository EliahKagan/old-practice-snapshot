#!/usr/bin/env python3

import collections
import itertools

def shortest_path(n):
    if n == 1:
        return 0

    vis = {1}
    queue = collections.deque((1,))

    for depth in itertools.count(1):
        for _ in range(len(queue)):
            src = queue.popleft()

            for dest in src + 1, src * 3:
                if dest in vis:
                    continue
                if dest == n:
                    return depth

                vis.add(dest)
                queue.append(dest)

def getval():
    return int(input())

for _ in range(getval()):
    print(shortest_path(getval()))
