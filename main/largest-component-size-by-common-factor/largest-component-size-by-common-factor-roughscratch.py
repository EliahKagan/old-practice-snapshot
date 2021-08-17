import math


def sieve(n):
    """Generates primes up to at least n with a Sieve of Eratosthenes."""
    yield 2
    
    table = [True] * (n + 1)  # true means possibly prime
    
    for factor in range(3, math.floor(math.sqrt(n)) + 1, 2):
        if table[factor]:
            for multiple in range(factor * factor, n + 1, factor * 2):
                table[multiple] = False
    
    for odd in range(3, n + 1, 2):
        if table[odd]:
            yield odd


PRIMES = tuple(sieve(100_000))
