class Solution:
    def licenseKeyFormatting(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        s = s.replace('-', '')
        groups = []

        while s:
            groups.append(s[-k:])
            s = s[:-k]

        return '-'.join(reversed(groups)).upper()
