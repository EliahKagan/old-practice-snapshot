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

        nonzeros = 0
        counts = [0] * ALPHA_LEN

        def inc(ch):
            nonlocal nonzeros
            k = ord(ch) - BIAS
            c = counts[k]
            if c == 0:
                nonzeros += 1
                counts[k] = 1
            elif c == -1:
                nonzeros -= 1
                counts[k] = 0
            else:
                counts[k] = c + 1

        def dec(ch):
            nonlocal nonzeros
            k = ord(ch) - BIAS
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
        for ch in p:
            inc(ch)
        for ch in s[:np]:
            dec(ch)
        if nonzeros == 0:
            ret.append(0)

        # all the other windows
        for i in range(ns - np):
            inc(s[i])
            dec(s[i + np])
            if nonzeros == 0:
                ret.append(i + 1)

        return ret