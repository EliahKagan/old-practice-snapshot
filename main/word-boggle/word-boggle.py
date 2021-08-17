#!/usr/bin/env python3

import itertools

class GridGraph(object):
    '''A non-reentrant graph implementation representing a Boggle grid.'''
    def __init__(self):
        '''Reads a grid from stdin and creates a graph for it.'''
        # Read the grid.
        self._m, self._n = map(int, input().split())
        self._grid = input().split()

        # Ensure the grid dimensions are consistent with its contents.
        if self._m * self._n != len(self._grid):
            raise ValueError('wrong record length while reading grid')

        # The graph's topology will be determined by the grid dimensions...
        cell_vertices = (tuple(self._adjacent_indices(i, j))
                         for (i, j) in self._grid_coords())

        # ...but with a final vertex: a virtual root with edges to each cell.
        root = tuple(range(self._m * self._n))

        # The adjacency list shall be (deeply) immutable: a tuple of tuples.
        self._adj = tuple(itertools.chain(cell_vertices, (root,)))
        assert len(self._adj) == self._m * self._n + 1

        # This on-board visitation list is why GridGraph isn't thread-safe.
        self._vis = [False] * len(self._adj)

    def __getitem__(self, vertex):
        '''Gets the character at the specified vertex.'''
        return self._grid[vertex]

    @property
    def adj(self):
        '''Gets the adjacency list, which is immutable.'''
        return self._adj

    @property
    def vis(self):
        '''Gets the visitation list, which the programmer may modify.'''
        return self._vis

    @property
    def root(self):
        '''Gets the root of the graph. (Returns -1, to index the end.)'''
        return -1

    def _adjacent_indices(self, i, j):
        '''Gets valid indices (i.e., vertex numbers) representing positions in
        the grid adjacent to the coordinates (i, j).'''
        for h, k in GridGraph._box_coords(i, j):
            if 0 <= h < self._m and 0 <= k < self._n and (h != i or k != j):
                yield h * self._n + k

    def _grid_coords(self):
        '''Generates the coordinates for the grid.'''
        return itertools.product(range(self._m), range(self._n))

    @staticmethod
    def _box_coords(i, j):
        '''Generates the coordinates of the 3-by-3 box centered at (i, j).'''
        return itertools.product(range(i - 1, i + 2), range(j - 1, j + 2))

class Trie(object):
    '''A prefix tree supporting traversal with a GridGraph, to solve Boggle.'''
    def __init__(self):
        self._word = None
        self._children = {}

    def add(self, word):
        '''Adds a word to the trie.'''
        cur = self

        for ch in word:
            try:
                cur = cur._children[ch]
            except KeyError:
                nxt = Trie()
                cur._children[ch] = nxt
                cur = nxt

        cur._word = word

    def search(self, graph):
        '''Finds all words that can be produced by adjacent letters in the
        GridGraph object :graph: with each vertex used only once per word.'''
        acc = set()
        self._dfs(graph, acc, graph.root)
        return acc

    def _dfs(self, graph, acc, v):
        '''Helper function for :search:. Performs depth-first search of the
        graph while traversing the trie, following only paths both permit.
        Accumulates matches into the set :acc:. Starts at the vertex :v:.'''
        if self._word is not None:
            acc.add(self._word)

        if self._children:
            graph._vis[v] = True

            for w in graph._adj[v]:
                if not graph._vis[w]:
                    try:
                        self._children[graph[w]]._dfs(graph, acc, w)
                    except KeyError:
                        pass

            graph._vis[v] = False

def read_words():
    x = int(input())
    words = list(input().split())
    if len(words) != x:
        raise ValueError('wrong record length while reading word list')
    return words

for _ in range(int(input())):
    trie = Trie()
    for word in read_words():
        trie.add(word)

    graph = GridGraph()
    matches = sorted(trie.search(graph))
    print(' '.join(matches) if matches else '-1')
