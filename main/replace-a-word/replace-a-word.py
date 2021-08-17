#!/usr/bin/python3

def gets():
    return input().strip()

for _ in range(int(input())):
    s = gets()
    old = gets()
    new = gets()
    print(s.replace(old, new))
