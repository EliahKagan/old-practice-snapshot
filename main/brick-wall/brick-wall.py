class Solution:
    def leastBricks(self, wall):
        """
        :type wall: List[List[int]]
        :rtype: int
        """
        # Convert each row to its partial sums.
        for row in wall:
            del row[-1]
            for j in range(1, len(row)):
                row[j] += row[j - 1]

        # Find how many don't share the commonest partial sum.
        counts = collections.Counter(itertools.chain.from_iterable(wall))
        best = counts.most_common(1)
        return len(wall) - best[0][1] if best else len(wall)
