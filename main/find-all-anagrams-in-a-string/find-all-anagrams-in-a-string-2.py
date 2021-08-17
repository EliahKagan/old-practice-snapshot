BIAS = ord('a')
ALPHA_LEN = 26
assert BIAS + ALPHA_LEN - 1 == ord('z')

class Solution:
    def findAnagrams(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: List[int]
        """
        ret = []
        ns = len(s)
        np = len(p)
        if ns < np:
            return ret

        s = tuple(ord(ch) - BIAS for ch in s)
        p = tuple(ord(ch) - BIAS for ch in p)

        nonzeros = 0
        counts = [0] * ALPHA_LEN

        def inc(k):
            nonlocal nonzeros
            c = counts[k]
            if c == 0:
                nonzeros += 1
                counts[k] = 1
            elif c == -1:
                nonzeros -= 1
                counts[k] = 0
            else:
                counts[k] = c + 1

        def dec(k):
            nonlocal nonzeros
            c = counts[k]
            if c == 0:
                nonzeros += 1
                counts[k] = -1
            elif c == 1:
                nonzeros -= 1
                counts[k] = 0
            else:
                counts[k] = c - 1

        # initial window
        for k in p:
            inc(k)
        for k  in s[:np]:
            dec(k)
        if nonzeros == 0:
            ret.append(0)

        # all the other windows
        for i in range(ns - np):
            inc(s[i])
            dec(s[i + np])
            if nonzeros == 0:
                ret.append(i + 1)

        return ret