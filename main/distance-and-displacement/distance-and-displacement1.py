from math import ceil
from math import sqrt

class BadCardinalDirectionError(ValueError):
    pass

class Sherlock: # represents Sherlock's state as he walks
    def __init__(self):
        self.__x = self.__y = self.__d = 0
    
    def get_mover(self, c):
        if c == 'N':
            def go(r):
                self.__y += r
        elif c == 'S':
            def go(r):
                self.__y -= r
        elif c == 'E':
            def go(r):
                self.__x += r
        elif c == 'W':
            def go(r):
                self.__x -= r
        else:
            raise BadCardinalDirectionError('invalid compass direction')
        
        def move(r):
            assert r >= 0
            go(r)
            self.__d += r
        
        return move
    
    def get_roundtrip_distance(self):
        return self.__d + int(ceil(sqrt(self.__x**2 + self.__y**2)))

for t in xrange(0, int(raw_input())):
    s = Sherlock()
    
    n = int(raw_input())
    magnitudes = map(int, raw_input().split())
    directions = map(s.get_mover, raw_input().strip())
    assert n == len(magnitudes) == len(directions)
    
    for i in xrange(0, n):
        directions[i](magnitudes[i])
    
    print s.get_roundtrip_distance()
