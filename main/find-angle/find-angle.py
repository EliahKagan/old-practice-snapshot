#!/usr/bin/env python3

from math import atan2, degrees

mAB = float(input())
mBC = float(input())
print(round(degrees(atan2(mAB, mBC))), end='°\n')
