#!/usr/bin/env python3

cube = lambda x: x**3

def fibonacci(n):
    ans = [0, 1]

    for _ in range(n - len(ans)):
        ans.append(ans[-2] + ans[-1])

    return ans[:n]

if __name__ == '__main__':
    n = int(input())
    print(list(map(cube, fibonacci(n))))
