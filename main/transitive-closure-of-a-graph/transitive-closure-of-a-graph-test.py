#!/usr/bin/env python3

from itertools import islice

def consume_adjacency_row(it, n, i):
    return tuple(e or i == j for (j, e) in enumerate(islice(it, n)))

def read_adjacency_matrix():
    n = int(input())
    it = map(bool, input().split())
    return tuple(consume_adjacency_row(it, n, i) for i in range(n))

def inner_product(row, col):
    return any(e and f for (e, f) in zip(row, col))

def matrix_multiply_row(row, b):
    return tuple(inner_product(row, col) for col in zip(*b))

def matrix_multiply(a, b):
    return tuple(matrix_multiply_row(row, b) for row in a)

def matrix_pow(base, exponent):
    if exponent == 1:
        return base

    root = matrix_pow(base, exponent // 2)
    square = matrix_multiply(root, root)
    return square if exponent % 2 == 0 else matrix_multiply(square, base)

def display(matrix):
    for row in matrix:
        print(*map(int, row))
    print()

a = ((True, True, False), (False, True, True), (False, False, True))
display(a)
display(matrix_pow(a, 2))
display(matrix_pow(a, 3))
print()

b = ((True, True, False, False),
     (False, True, True, False),
     (False, False, True, True),
     (False, False, False, True))
display(b)
display(matrix_pow(b, 2))
display(matrix_pow(b, 3))
