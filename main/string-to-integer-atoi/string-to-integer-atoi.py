class Solution:
    def __init__(self):
        self._INT_MIN = -2**31
        self._INT_MAX = 2**31 - 1
        self._BASE = 10

    def myAtoi(self, text):
        """
        :type text: str
        :rtype: int
        """
        text = text.strip()
        if not text:
            return 0

        sign = +1
        if text[0] in '+-':
            if text[0] == '-':
                sign = -1
            text = text[1:]

        acc = 0
        for ch in text:
            if not ch.isdigit():
                break
            d = ord(ch) - ord('0')
            assert 0 <= d < self._BASE
            acc = acc * self._BASE + d

        return min(max(acc * sign, self._INT_MIN), self._INT_MAX)
