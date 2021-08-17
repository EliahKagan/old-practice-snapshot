#!/usr/bin/env python3

def read_binary_fixed(): # interprets input as a fixed-point binary number
    left, right = input().strip().split('.')
    return int(left, 2) + int(right, 2) / float(2**len(right))

for t in range(int(input())):
    print(read_binary_fixed())
