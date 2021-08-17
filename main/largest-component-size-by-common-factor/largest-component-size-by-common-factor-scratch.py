import bisect
import itertools
import math


class DisjointSets:
    """
    Disjoint-set union data structure in which each element contributes an
    arbitrary measure.
    """

    __slots__ = ('_parents', '_ranks', '_measures')

    def __init__(self, measures):
        """
        Constructs DisjointSets with a fixed number of elements, each initially
        in a singleton. That is, it is as if a makeset operation is performed
        for each element and corresponding measure (element, measure) in
        enumerate(measures).
        """
        self._measures = list(measures)
        length = len(self._measures)
        self._parents = list(range(length))
        self._ranks = [0] * length

    def max_combined_measure(self):
        """
        Returns the highest measure of any current set.
        Assumes no element has negative measure.
        """
        return max(self._measures)

    def union(self, element1, element2):
        """Combines the sets containing the given elements into a single set."""
        # Find the ancestors and stop if they are already the same.
        element1 = self._find_set(element1)
        element2 = self._find_set(element2)
        if element1 == element2:
            return

        # Unite by rank.
        if self._ranks[element1] < self._ranks[element2]:
            self._join(element2, element1)
        else:
            if self._ranks[element1] == self._ranks[element2]:
                self._ranks[element1] += 1
            self._join(element1, element2)

    def _find_set(self, element):
        """Finds the representative of the set contaiing the given element."""
        # Find the ancestor.
        leader = element
        while leader != self._parents[leader]:
            leader = self._parents[leader]

        # Compress the path.
        while element != leader:
            self._parents[element], element = leader, self._parents[element]

        return leader

    def _join(self, parent, child):
        """Joins the child to the parent."""
        self._parents[child] = parent
        self._measures[parent] += self._measures[child]


def sieve(bound):
    """Yields primes up to at least `bound` with a Sieve of Eratosthenes."""
    yield 2

    table = [True] * (bound + 1)  # True means possibly prime.

    for factor in range(3, math.floor(math.sqrt(bound)) + 1, 2):
        if table[factor]:
            for multiple in range(factor * factor, bound + 1, factor * 2):
                table[multiple] = False

    for odd in range(3, bound + 1, 2):
        if table[odd]:
            yield odd


PRIMES = tuple(sieve(100_000))

assert PRIMES, 'as implemented, the algorithms need a non-empty PRIMES table'


def prime_factor_indices(product):
    """
    Yields the `PRIMES` table index of each unique prime factor of `product`,
    in ascending order.
    """
    for index, prime in enumerate(PRIMES):
        if prime * prime > product:
            break

        if product % prime == 0:
            yield index
            product //= prime

        while product % prime == 0:
            product //= prime

    if product != 1:
        index = bisect.bisect_left(PRIMES, product)
        print(f'product={product}, index={index}, prime={PRIMES[index]}')
        assert PRIMES[index] == product, 'product should be down to one prime'
        yield index


class Solution:
    @staticmethod
    def largestComponentSize(values: List[int]) -> int:
        bias = len(PRIMES)
        sets = DisjointSets(itertools.chain(itertools.repeat(0, bias),
                                            itertools.repeat(1, len(values))))

        for value_index, value in enumerate(values):
            biased_value_index = bias + value_index
            for prime_index in prime_factor_indices(value):
                sets.union(prime_index, biased_value_index)

        return sets.max_combined_measure()
