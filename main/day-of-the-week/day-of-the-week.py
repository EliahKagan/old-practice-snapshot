#!/usr/bin/env python3

from datetime import date

for _ in range(int(input())):
    d, m, y = map(int, input().split())
    print(date(y, m, d).strftime("%A"))
