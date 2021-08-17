class Codec:
    def __init__(self):
        self._cur = ''
        self._map = {}

    def encode(self, long_url):
        """Encodes a URL to a shortened URL.

        :type long_url: str
        :rtype: str
        """
        self._advance()
        short_url = Codec._PREFIX + self._cur
        self._map[short_url] = long_url
        return short_url

    def decode(self, short_url):
        """Decodes a shortened URL to its original URL.

        :type short_url: str
        :rtype: str
        """
        return self._map[short_url]

    def _advance(self):
        index = self._nonmax_index()
        
        if index is None:
            self._cur = Codec._DIGITS[0] * (len(self._cur) + 1)
        else:
            self._cur = (Codec._DIGITS[0] * index
                         + Codec._increment(self._cur[index])
                         + self._cur[(index + 1):])

    def _nonmax_index(self):
        it = (index for index, digit in enumerate(self._cur)
              if digit != Codec._DIGITS[-1])
        
        return next(it, None)

    @staticmethod
    def _increment(digit):
        return Codec._DIGITS[Codec._ORDINALS[digit] + 1]

    _PREFIX = 'http://example.com/'
    _DIGITS = string.digits + string.ascii_letters
    _ORDINALS = {digit: ordinal for ordinal, digit in enumerate(_DIGITS)}


# Your Codec object will be instantiated and called as such:
# codec = Codec()
# codec.decode(codec.encode(url))
