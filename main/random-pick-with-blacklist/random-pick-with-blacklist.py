class Solution:
    def __init__(self, N, blacklist):
        """
        :type N: int
        :type blacklist: List[int]
        """
        obverse = {}  # index -> element
        inverse = {}  # element -> index
        j = N

        for x in blacklist:
            # find the current mappings in both directions
            j -= 1
            y = obverse.get(j, j)
            i = inverse.get(x, x)

            # do a swap by updating mappings in both directions
            obverse[i] = y
            obverse[j] = x
            inverse[x] = j
            inverse[y] = i

        # obverse records all the non-stationary indices in [0, j)
        self._last = j - 1
        self._special = obverse

    def pick(self):
        """
        :rtype: int
        """
        i = random.randint(0, self._last)
        return self._special.get(i, i)


# Your Solution object will be instantiated and called as such:
# obj = Solution(N, blacklist)
# param_1 = obj.pick()
