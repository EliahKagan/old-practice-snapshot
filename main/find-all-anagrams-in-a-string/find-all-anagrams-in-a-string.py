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

        cs = self._count(s[:np])
        cp = self._count(p)
        if cs == cp:
            ret.append(0)

        for i in range(ns - np):
            cs[ord(s[i]) - BIAS] -= 1
            cs[ord(s[i + np]) - BIAS] += 1
            if cs == cp:
                ret.append(i + 1)

        return ret

    def _count(self, chars):
        counts = [0] * ALPHA_LEN
        for ch in chars:
            counts[ord(ch) - BIAS] += 1
        return counts
