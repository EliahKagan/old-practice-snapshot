class Solution:
    def validPalindrome(self, s):
        """
        :type s: str
        :rtype: bool
        """
        i = 0
        j = len(s) - 1
        while i < j:
            if s[i] != s[j]:
                return self._validWithout(s, i) or self._validWithout(s, j)
            i += 1
            j -= 1

        return True

    def _validWithout(self, s, k):
        r = s[:k] + s[k + 1:]
        return r == r[::-1]
