#!/usr/bin/env python3

from collections import deque

deq = deque()

for _ in range(int(input())):
    tok = input().split()

    if tok[0] == 'append':
        deq.append(int(tok[1]))
    elif tok[0] == 'pop':
        deq.pop()
    elif tok[0] == 'appendleft':
        deq.appendleft(int(tok[1]))
    elif tok[0] == 'popleft':
        deq.popleft()

print(*deq)
