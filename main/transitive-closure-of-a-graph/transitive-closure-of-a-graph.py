#!/usr/bin/env python3

from itertools import chain, islice

def consume_adjacency_row(it, n, i):
    return tuple(e or i == j for (j, e) in enumerate(islice(it, n)))

def read_adjacency_matrix():
    n = int(input())
    it = map(int, input().split())
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
    print(*map(int, chain.from_iterable(matrix)))

for _ in range(int(input())):
    a = read_adjacency_matrix()

    if len(a) == 1:
        print('1')
    else:
        display(matrix_pow(a, len(a) - 1))
