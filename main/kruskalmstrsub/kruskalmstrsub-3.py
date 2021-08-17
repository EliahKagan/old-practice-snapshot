#!/usr/bin/env python3

from collections import namedtuple
from itertools import starmap

def read_record():
    return map(int, input().split())

n, m = read_record()

vertices =  [-1] * (n + 1)  # add 1 since we're not using vertics[0]

def find_set(i):
    '''Gets the representative element of the set that contains i.'''
    # find the ancestor
    j = i
    while vertices[j] >= 0:
        j = vertices[j]

    # compress the path
    while i != j:
        vertices[i], i = j, vertices[i]

    return j

def union(i, j):
    '''If i and j are in different sets, joins those sets and returns True.
    If they were already in the same set, returns False.'''
    # find the roots and check if i and j are actually in separate sets
    i = find_set(i)
    j = find_set(j)
    if i == j:
        return False

    # union by rank
    if vertices[i] > vertices[j]:
        vertices[i] = j  # j has superior (more negative) rank
    else:
        if vertices[i] == vertices[j]:
            vertices[i] -= 1  # i and j have same rank, so promote i

        vertices[j] = i  # i has superior (more negative) rank

    return True

Edge = namedtuple('Edge', ('x', 'y', 'r'))

# Read all m edges and sort them nondecreasingly by weight. There is no need
# to break ties, since we just need the total weight of the "Really Special
# Subtree," and all a graph's MSTs have the same total weight as one another.
records = (read_record() for _ in range(m))
edges = sorted(starmap(Edge, records), key = lambda edge: edge.r)

# Sum the weights of edges whose inclusion increases connectivity.
print(sum(edge.r for edge in edges if union(edge.x, edge.y)))
