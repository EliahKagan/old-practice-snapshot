#!/usr/bin/env python3


def read_record():
    """Reads a line of input as a sequence of integers."""
    return map(int, input().split())


def fib_modified(a, b, n):
    """Computes the modified Fiboniacci-style function."""
    for _ in range(2, n):
        a, b = b, a + b * b
    return b


if __name__ == '__main__':
    print(fib_modified(*read_record()))
