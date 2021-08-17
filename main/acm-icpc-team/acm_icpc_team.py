#!/usr/bin/env python3

best = -1       # the most topics any one team knows
best_teams = 0  # count of teams that know that many

n, _ = map(int, input().split()) # don't need m
a = [int(input(), 2) for _ in range(n)]

for i in range(0, n - 1):
    for j in range(i + 1, n):
        cur = bin(a[i] | a[j]).count('1')
        
        if best < cur:
            best = cur
            best_teams = 1
        elif best == cur:
            best_teams += 1

print(best)
print(best_teams)
