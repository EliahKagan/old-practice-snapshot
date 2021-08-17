#!/usr/bin/env python3

def wrapper(f):
    return lambda l: f('+91 {} {}'.format(s[-10:-5], s[-5:]) for s in l)

@wrapper
def sort_phone(l):
    print(*sorted(l), sep='\n')

if __name__ == '__main__':
    l = [input() for _ in range(int(input()))]
    sort_phone(l)
