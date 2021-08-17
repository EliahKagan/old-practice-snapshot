#!/usr/bin/env python3

def read_val():
    return int(input())

def read_matrix():
    n = read_val()
    
    def read_row():
        row = list(map(int, input().split()))
        if len(row) != n:
            raise ValueError('wrong row size')
        return row
    
    return [read_row() for _ in range(n)]

def row_sums(a):
    return map(sum, a)

def col_sums(a):
    for i in range(len(a)):
        yield sum(row[i] for row in a)

for _ in range(read_val()):
    # We need the bag of container sizes (number of balls in each container)
    # to be equal to the bag of color counts (number of balls of each color).
    a = read_matrix()
    container_sizes = sorted(row_sums(a))
    color_counts = sorted(col_sums(a))
    print('Possible' if container_sizes == color_counts else 'Impossible')
