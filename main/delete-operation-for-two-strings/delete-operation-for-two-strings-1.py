class Solution:
    def minDistance(self, s: str, t: str) -> int:
        """Modified Wagner-Fischer algorithm"""
        if len(s) < len(t):
            s, t = t, s

        pre = [None] * (len(t) + 1)
        cur = list(range(len(pre)))

        for i, sc in enumerate(s, 1):
            pre, cur = cur, pre
            cur[0] = i

            for j, tc in enumerate(t, 1):
                cur[j] = pre[j - 1] if sc == tc else 1 + min(cur[j - 1], pre[j])

        return cur[-1]
