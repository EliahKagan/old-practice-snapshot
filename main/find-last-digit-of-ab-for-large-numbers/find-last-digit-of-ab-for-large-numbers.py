#!/usr/bin/env python3

for _ in range(int(input())):
    astr, bstr = input().split()
    a = int(astr[-1])
    b = int(bstr)
    print(pow(a, b, 10))
