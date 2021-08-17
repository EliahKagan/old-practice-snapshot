#!/usr/bin/env python3

DIVISOR = 4

for _ in range(int(input())):
    input() # don't need n
    a = list(map(int, input().split()))
    
    count = 0;
    for i in range(0, len(a) - 1):
        for j in range(i + 1, len(a)):
            if (a[i] + a[j]) % DIVISOR == 0:
                count += 1
    
    print(count)
