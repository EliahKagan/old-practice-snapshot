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

        # initial window
        counts = [0] * ALPHA_LEN
        for ch in p:
            counts[ord(ch) - BIAS] += 1
        for ch in s[:np]:
            counts[ord(ch) - BIAS] -= 1
        if not any(counts):
            ret.append(0)

        # all the other windows
        for i in range(ns - np):
            counts[ord(s[i]) - BIAS] += 1
            counts[ord(s[i + np]) - BIAS] -= 1
            if not any(counts):
                ret.append(i + 1)

        return ret
