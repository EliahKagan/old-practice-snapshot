#!/usr/bin/env python3

def heap_height(size):
    height = 0

    width = 1
    while size > 0:
        height += 1
        size -= width
        width *= 2

    return height

for _ in range(int(input())):
    size = int(input())
    input() # don't need elements
    print(heap_height(size))
