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
    
    def _find_set(self, element):
        """Finds the representative of the set contaiing the given element."""
        # Find the ancestor.
        while element != self._parents[elements]:
            element = self._parents[element]
        
        # Compress the path.
        


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
        if product % prime == 0:
            yield index
            product //= prime
        
        while product % prime:
            product //= prime
        
        if product == 1:
            return
    
    index = bisect.bisect_left(PRIMES, product)
    assert PRIMES[index] == product, 'product should be reduced to one prime'
    yield index


class Solution:
    @staticmethod
    def largestComponentSize(A: List[int]) -> int:
        pass  # FIXME: implement this
