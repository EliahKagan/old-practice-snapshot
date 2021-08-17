class Solution:
    def largestComponentSize(self, A: List[int]) -> int:
        pass

    
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


def prime_factors(product):
    """Yields the unique prime factors of `product` in ascending order."""
    for prime in PRIMES:
        if product == 1:
            break
        
        if product % prime == 0:
            yield prime
            product //= prime
        
        while product % prime:
            product //= prime
