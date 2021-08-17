''' Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above. '''

import heapq

BIG = 2**31 - 1

# Your task is to complete this function
# The function prints V space separated integers where
# the ith integer denote the shortest distance of ith vertex
# from source vertex
def dijkstra(graph, v, s):
    assert(len(graph) == v)
    costs = [BIG] * v
    heap = [(0, s)]

    while heap:
        cost, src = heapq.heappop(heap)
        assert cost != BIG
        if costs[src] != BIG:
            continue

        costs[src] = cost

        assert len(graph[src]) == v
        for dest, weight in enumerate(graph[src]):
            if weight != 0 and costs[dest] == BIG:
                heapq.heappush(heap, (cost + weight, dest))

    print(*costs, end='')
