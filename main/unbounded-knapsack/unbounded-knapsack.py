#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

def solve_knapsack(values, target):
    memo = {}

    def solve(index, subtot):
        try:
            value = values[index]
            subproblem_key = (index, subtot)
            return memo[subproblem_key]
        except IndexError:
            return subtot
        except KeyError:
            candidates = (solve(index + 1, next_subtot)
                          for next_subtot in range(subtot, target + 1, value))
            ret = max(candidates, default=0)
            memo[subproblem_key] = ret
            return ret

    return solve(0, 0)

for _ in range(int(input())):
    _, target = read_record()
    values = list(set(read_record()))
    print(solve_knapsack(values, target))
