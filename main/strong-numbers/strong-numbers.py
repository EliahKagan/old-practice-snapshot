#!/usr/bin/env python3

def get_factorial(nmax):
    fac = [1]
    
    for i in range(1, nmax + 1):
        fac.append(fac[-1] * i)
    
    return fac

fac = get_factorial(9)

for t in range(int(input())):
    value = input().strip()
    fac_sum = sum(fac[ord(d) - ord('0')] for d in value)
    print('1' if fac_sum == int(value) else '0')
