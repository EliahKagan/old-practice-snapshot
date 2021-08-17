class Solution:
    def longestCommonPrefix(self, strs):
        """
        :type strs: List[str]
        :rtype: str
        """
        if not strs:
            return ''

        n = min(map(len, strs))
        s = strs[0]

        i = 0
        while i != n and all(t[i] == s[i] for t in strs):
            i += 1

        return s[:i]
