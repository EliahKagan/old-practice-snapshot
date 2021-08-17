#!/usr/bin/env python3

for t in range(int(input())):
    print(input().split()[-1]) # line is (vertex count, edge count)
    input() # we don't need the graph itself, just the edge count
