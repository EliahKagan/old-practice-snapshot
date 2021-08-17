#!/usr/bin/env python3

import datetime

def read_datetime():
    return datetime.datetime.strptime(input(), '%a %d %b %Y %X %z')

for _ in range(int(input())):
    t1 = read_datetime()
    t2 = read_datetime()
    dtsec = (t1 - t2).total_seconds()
    print('{:.0f}'.format(abs(dtsec)))
