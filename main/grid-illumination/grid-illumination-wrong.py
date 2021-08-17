class Solution:
    def gridIllumination(self, N: int, lamps: List[List[int]], queries: List[List[int]]) -> List[int]:
        cells = {(x, y) for x, y in lamps}
        ranks = collections.Counter(x for x, y in lamps)
        files = collections.Counter(y for x, y in lamps)
        inclines = collections.Counter(x - y for x, y in lamps)
        declines = collections.Counter(x + y for x, y in lamps)

        def darken(x, y):
            try:
                cells.remove((x, y))
            except KeyError:
                return

            ranks[x] -= 1
            files[y] -= 1
            inclines[x - y] -= 1
            declines[x + y] -= 1

        def query(x, y):
            result = ranks[x] or files[y] or inclines[x - y] or declines[x + y]

            for h in x - 1, x + 2:
                for k in y - 1, y + 2:
                    darken(h, k)

            return 1 if result else 0

        return [query(x, y) for x, y in queries]
