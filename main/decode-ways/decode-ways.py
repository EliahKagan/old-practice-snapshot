class Solution:
    def numDecodings(self, s):
        """
        :type s: str
        :rtype: int
        """
        if not s:
            return 0 # really 1, but the leetcode.com OJ wants 0

        far = 1
        near = 0 if s[-1] == '0' else 1

        for i in range(len(s) - 2, -1, -1):
            here = 0

            if s[i] != '0':
                here += near # we can move right by one
                if int(s[i:(i + 2)]) <= 26:
                    here += far # or we can move right by two

            far = near
            near = here

        return near
